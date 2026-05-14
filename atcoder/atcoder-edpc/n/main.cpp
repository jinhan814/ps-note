#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector psum(n + 1, i64(0));
	for (int i = 0; i < n; i++) {
		psum[i + 1] = psum[i] + v[i];
	}
	vector dp(n, vector(n, i64(0)));
	for (int len = 2; len <= n; len++) {
		for (int l = 0; l + len - 1 < n; l++) {
			int r = l + len - 1;
			dp[l][r] = i64(1) << 60;
			for (int k = l; k < r; k++) {
				i64 v1 = dp[l][k] + dp[k + 1][r];
				i64 v2 = psum[r + 1] - psum[l];
				dp[l][r] = min(dp[l][r], v1 + v2);
			}
		}
	}
	return dp[0][n - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}