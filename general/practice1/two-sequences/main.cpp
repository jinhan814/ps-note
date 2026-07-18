#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2'000'000'000;

auto sol = [](int n, int m, auto a, auto b) {
	vector p1(n + 1, 0);
	vector p2(m + 1, 0);
	for (int i = 0; i < n; i++) p1[i + 1] = p1[i] + a[i] - 1;
	for (int i = 0; i < m; i++) p2[i + 1] = p2[i] + b[i] - 1;
	vector c1(n + 1, inf);
	vector c2(m + 1, inf);
	vector dp(n + 1, vector(m + 1, inf));
	c1[0] = 0;
	c2[0] = 0;
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int v1 = p1[i] - p1[i - 1];
			int v2 = p2[j] - p2[j - 1];
			c1[i - 1] = min(c1[i - 1], dp[i - 1][j - 1] - p2[j - 1] * v1);
			c2[j - 1] = min(c2[j - 1], dp[i - 1][j - 1] - p1[i - 1] * v2);
			dp[i][j] = min(c1[i - 1] + p2[j] * v1, c2[j - 1] + p1[i] * v2);
		}
	}
	return dp[n][m];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}