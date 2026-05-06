#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, auto v) {
	vector dp(1, f64(1));
	for (int i = 0; i < n; i++) {
		vector ndp(i + 2, f64(0));
		for (int x = 0; x <= i; x++) {
			ndp[x] += dp[x] * (1 - v[i]);
			ndp[x + 1] += dp[x] * v[i];
		}
		dp.swap(ndp);
	}
	f64 ret = 0;
	for (int i = (n + 1) / 2; i <= n; i++) ret += dp[i];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, f64(0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << fixed << setprecision(20);
	cout << sol(n, v) << '\n';
}