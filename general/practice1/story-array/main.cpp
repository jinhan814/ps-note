#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector c(q, 0);
	iota(c.begin(), c.end(), 0);
	sort(c.begin(), c.end(), [&](int i, int j) { return qs[i][1] < qs[j][1]; });
	sort(v.begin(), v.end(), [](auto a, auto b) { return a[1] < b[1]; });
	vector dp(1'000'001, -1);
	dp[0] = 0;
	vector ret(q, false);
	for (int i = 0, j = 0; i < q; i++) {
		int p = c[i];
		while (j < n && v[j][1] <= qs[p][1]) {
			for (int x = 1'000'000; x >= v[j][0]; x--) {
				if (dp[x - v[j][0]] == -1) continue;
				dp[x] = max(dp[x], dp[x - v[j][0]] + v[j][1]);
			}
			j++;
		}
		ret[p] = dp[qs[p][0]] >= qs[p][1];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, array{ 0, 0 });
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << (res[i] ? "YES" : "NO") << '\n';
}