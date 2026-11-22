#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, int a, int b, auto v, auto c) {
	vector dp(m + 1, vector(301, -1));
	dp[0][a] = b;
	for (auto [v1, v2] : v) {
		for (int i = m; i >= 1; i--) {
			for (int x = 0; x <= 300; x++) {
				if (dp[i - 1][x] == -1) continue;
				int nx = min(x + v1, 300);
				dp[i][nx] = max(dp[i][nx], dp[i - 1][x] + v2);
			}
		}
	}
	int ret = 0;
	for (int x = 0; x <= 300; x++) {
		int cnt = 0;
		for (int i = 0; i < k; i++) {
			if (c[i][0] > x) continue;
			if (c[i][1] > dp[m][x]) continue;
			cnt++;
		}
		ret = max(ret, cnt);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b; cin >> n >> m >> a >> b;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	int k; cin >> k;
	vector c(k, array{ 0, 0 });
	for (int i = 0; i < k; i++) cin >> c[i][0] >> c[i][1];
	cout << sol(n, m, k, a, b, v, c) << '\n';
}