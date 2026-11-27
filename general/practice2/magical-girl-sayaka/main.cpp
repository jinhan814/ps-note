#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v, auto c) {
	sort(v.begin(), v.end());
	vector p(m + 1, i64(0));
	for (int i = 0; i < m; i++) p[i + 1] = p[i] + c[i];
	auto f = [&](int i, int j) { return (p[v[j]] - p[v[i] - 1]) / k; };
	vector dp(n, vector(n, i64(0)));
	for (int i = 1; i <= n - 1; i++) dp[0][i] = dp[0][i - 1] + f(i - 1, i);
	for (int i = 1; i <= n - 2; i++) {
		dp[i][i + 1] = i64(1) << 60;
		for (int j = 0; j <= i - 1; j++) dp[i][i + 1] = min(dp[i][i + 1], dp[j][i] + f(j, i + 1));
		for (int j = i + 2; j <= n - 1; j++) dp[i][j] = dp[i][j - 1] + f(j - 1, j);
	}
	i64 ret = i64(1) << 60;
	for (int i = 0; i <= n - 2; i++) ret = min(ret, dp[i][n - 1] + f(i, n - 1));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0), c(m, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < m; i++) cin >> c[i];
	cout << sol(n, m, k, v, c) << '\n';
}