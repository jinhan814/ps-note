#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, auto v) {
	vector dp(1 << n, f64(1));
	for (int bit = 1; bit <= n; bit++) {
		vector ndp(1 << n, f64(0));
		int sz = 1 << (bit - 1);
		for (int l = 0; l < 1 << n; l += 2 * sz) {
			int r = l + sz - 1;
			for (int i = l; i <= r; i++) {
				for (int j = l + sz; j <= r + sz; j++) {
					f64 v1 = dp[i] * dp[j];
					f64 v2 = 1 / (1 + pow(10, f64(v[j] - v[i]) / 400));
					ndp[i] += v1 * v2;
					ndp[j] += v1 * (1 - v2);
				}
			}
		}
		dp.swap(ndp);
	}
	return dp;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(1 << n, 0);
	for (int i = 0; i < 1 << n; i++) cin >> v[i];
	auto res = sol(n, v);
	cout << fixed << setprecision(20);
	for (int i = 0; i < 1 << n; i++) cout << res[i] << '\n';
}