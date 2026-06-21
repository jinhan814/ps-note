#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto a, auto b) {
	vector dp(n + 1, vector(m + 1, i64(0)));
	for (int i = 0; i < n; i++) {
		dp[i + 1] = dp[i];
		for (int j = a[i]; j <= m; j++) {
			i64 val = dp[i][j - a[i]] + b[i];
			dp[i + 1][j] = max(dp[i + 1][j], val);
		}
	}
	string ret(n, 0);
	vector c(m + 1, i64(0));
	for (int i = n - 1; i >= 0; i--) {
		vector p(m + 1, -(i64(1) << 60));
		for (int j = a[i]; j <= m; j++) p[j] = c[j - a[i]] + b[i];
		i64 opt1 = 0, opt2 = 0;
		for (int j = 0; j <= m; j++) {
			i64 v1 = c[j] + dp[i][m - j];
			i64 v2 = p[j] + dp[i][m - j];
			opt1 = max(opt1, v1);
			opt2 = max(opt2, v2);
		}
		for (int j = a[i]; j <= m; j++) c[j] = max(c[j], p[j]);
		if (opt1 < opt2) ret[i] = 'A';
		else if (opt1 == opt2) ret[i] = 'B';
		else ret[i] = 'C';
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, m, a, b) << '\n';
}