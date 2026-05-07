#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector c(n, 0);
	iota(c.begin(), c.end(), 1);
	sort(c.begin(), c.end(), [&](int i, int j) {
		return i64(v[i]) * j > i64(v[j]) * i;
	});
	vector dp(n * c[0] + 1, i64(0));
	for (int i = 1; i <= n * c[0]; i++) {
		int lim = (3 * n * n + i - 1) / i;
		if (lim > n) lim = n;
		for (int j = 0; j < lim; j++) {
			if (i < c[j]) continue;
			dp[i] = max(dp[i], dp[i - c[j]] + v[c[j]]);
		}
	}
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		int x = qs[i];
		if (x > n * c[0]) {
			int k = (x - n * c[0] + c[0] - 1) / c[0];
			ret[i] += i64(k) * v[c[0]];
			x -= k * c[0];
		}
		ret[i] += dp[x];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}