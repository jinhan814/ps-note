#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int ret = 1 << 30;
	vector dp(n, vector(m, 1 << 30));
	dp[0][0] = 0;
	for (int iter = 0; iter < n * m; iter++) {
		vector ndp(n, vector(m, 1 << 30));
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				for (int i = 0; i < 4; i++) {
					int nx = x + "1012"[i] - '1';
					int ny = y + "2101"[i] - '1';
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
					int val = dp[x][y] + v[nx][ny] * (2 * iter + 1) + 1;
					ndp[nx][ny] = min(ndp[nx][ny], val);
				}
			}
		}
		dp.swap(ndp);
		ret = min(ret, dp[n - 1][m - 1] - iter - 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, v) << '\n';
}