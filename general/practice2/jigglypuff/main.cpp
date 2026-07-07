#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector dp(m, false);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (v[i - 1][j] != v[i][j - 1]) continue;
			if (dp[j - 1]) return true;
			if (i + 1 < n && v[i][j] == v[i + 1][j - 1]) return true;
			if (j + 1 < m && v[i][j] == v[i - 1][j + 1]) return true;
		}
		for (int j = 1; j < m; j++) {
			if (dp[j - 1]) dp[j] = true;
			if (v[i - 1][j] != v[i][j - 1]) continue;
			dp[j] = true;
		}
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, m, v) ? "YES" : "NO") << '\n';
}