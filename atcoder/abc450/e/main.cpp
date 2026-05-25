#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](string a, string b, int q, auto qs) {
	vector pa(a.size() + 1, vector(26, 0));
	vector pb(b.size() + 1, vector(26, 0));
	for (int i = 0; i < a.size(); i++) {
		pa[i + 1] = pa[i];
		pa[i + 1][a[i] - 'a']++;
	}
	for (int i = 0; i < b.size(); i++) {
		pb[i + 1] = pb[i];
		pb[i + 1][b[i] - 'a']++;
	}
	vector dp(0, array{ i64(0), i64(0), i64(0) });
	dp.push_back(array{ i64(a.size()), i64(1), i64(0) });
	dp.push_back(array{ i64(b.size()), i64(0), i64(1) });
	for (int i = 2; dp[i - 1][0] <= i64(1e18); i++) {
		i64 v1 = dp[i - 1][0] + dp[i - 2][0];
		i64 v2 = dp[i - 1][1] + dp[i - 2][1];
		i64 v3 = dp[i - 1][2] + dp[i - 2][2];
		dp.push_back(array{ v1, v2, v3 });
	}
	auto rec = [&](const auto& self, int dep, i64 n, int x) -> i64 {
		if (dep == 0) return pa[n][x];
		if (dep == 1) return pb[n][x];
		if (n <= dp[dep - 1][0]) return self(self, dep - 1, n, x);
		i64 v1 = pa[a.size()][x] * dp[dep - 1][1];
		i64 v2 = pb[b.size()][x] * dp[dep - 1][2];
		i64 v3 = self(self, dep - 2, n - dp[dep - 1][0], x);
		return v1 + v2 + v3;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [l, r, x] = qs[i];
		i64 v1 = rec(rec, dp.size() - 1, r, x - 'a');
		i64 v2 = rec(rec, dp.size() - 1, l - 1, x - 'a');
		ret[i] = v1 - v2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a, b; cin >> a >> b;
	int q; cin >> q;
	vector qs(q, tuple(i64(0), i64(0), ' '));
	for (auto& [l, r, x] : qs) cin >> l >> r >> x;
	auto res = sol(a, b, q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}