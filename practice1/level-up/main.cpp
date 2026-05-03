#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr i64 inf = i64(1) << 60;

auto sol = [](int n, int m, int k, auto v) {
	sort(v.begin(), v.end());
	vector dp(m + 1, vector(m + k + 1, inf));
	dp[0][0] = 0;
	for (auto [a, b, c, d] : v) {
		for (int i = m + k - 1; i >= 0; i--){
			if (dp[m][i] == inf) continue;
			int ni = min(i + c, m + k);
			dp[m][ni] = min(dp[m][ni], dp[m][i] + d);
		}
		for (int i = m - 1; i >= 0; i--) {
			for (int j = m + k; j >= 0; j--) {
				if (dp[i][j] == inf) continue;
				int ni1 = min(i + a, m);
				int nj1 = min(j + a, m + k);
				int ni2 = i;
				int nj2 = min(j + c, m + k);
				dp[ni1][nj1] = min(dp[ni1][nj1], dp[i][j] + b);
				dp[ni2][nj2] = min(dp[ni2][nj2], dp[i][j] + d);
			}
		}
	}
	if (dp[m][m + k] == inf) return i64(-1);
	return dp[m][m + k];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, array{ 0, 0, 0, 0 });
	for (auto& [a, b, c, d] : v) cin >> a >> b >> c >> d;
	cout << sol(n, m, k, v) << '\n';
}