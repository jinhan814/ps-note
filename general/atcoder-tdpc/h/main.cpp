#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector buc(51, vector(0, pair(0, 0)));
	for (auto [a, b, c] : v) buc[c].push_back(pair(a, b));
	vector dp(k + 1, vector(m + 1, 0));
	for (int iter = 1; iter <= 50; iter++) {
		if (buc[iter].empty()) continue;
		vector c(k + 1, vector(m + 1, 0));
		for (auto [a, b] : buc[iter]) {
			for (int i = 1; i <= k; i++) {
				for (int x = m; x >= a; x--) {
					c[i][x] = max(c[i][x], c[i][x - a] + b);
					c[i][x] = max(c[i][x], dp[i - 1][x - a] + b);
				}
			}
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j] = max(dp[i][j], c[i][j]);
			}
		}
	}
	int ret = 0;
	for (int i = 1; i <= k; i++) ret = max(ret, dp[i][m]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, tuple(0, 0, 0));
	for (auto& [a, b, c] : v) cin >> a >> b >> c;
	cout << sol(n, m, k, v) << '\n';
}