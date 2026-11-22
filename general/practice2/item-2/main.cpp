#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector p(n + 1, i64(0));
	for (int i = 0; i < n; i++) {
		p[i + 1] = p[i] + v[i];
	}
	vector dp(n + 1, -(i64(1) << 60));
	for (int i = 0; i <= m; i++) dp[i] = p[i];
	for (int i = m + 1; i <= n; i++) {
		if (i - m >= 1) dp[i - m] = max(dp[i - m], dp[i - m - 1]);
		dp[i] = max(dp[i], dp[i - m] + p[i] - p[i - m]);
		dp[i] = max(dp[i], dp[i - 1] + v[i - 1]);
	}
	for (int i = 1; i <= n; i++) {
		dp[i] = max(dp[i], dp[i - 1]);
	}
	i64 ret = dp[n];
	for (int i = n - m + 1; i <= n; i++) {
		ret = max(ret, dp[i - 1] + p[n] - p[i - 1]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}