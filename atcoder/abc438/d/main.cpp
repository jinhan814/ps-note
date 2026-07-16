#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto a, auto b, auto c) {
	for (int i = 1; i <= n; i++) {
		a[i] += a[i - 1];
		b[i] += b[i - 1];
		c[i] += c[i - 1];
	}
	vector dp(n, i64(0));
	for (int i = n - 1; i >= 1; i--) {
		dp[i] = c[n] - c[i];
		if (i + 1 < n) dp[i] = max(dp[i], dp[i + 1]);
		dp[i] += b[i] - b[i - 1];
	}
	i64 ret = 0;
	for (int i = 1; i <= n - 2; i++) ret = max(ret, a[i] + dp[i + 1]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n + 1, i64(0)), b(n + 1, i64(0)), c(n + 1, i64(0));
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	cout << sol(n, a, b, c) << '\n';
}