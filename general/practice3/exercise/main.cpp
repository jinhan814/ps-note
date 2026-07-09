#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector c(2 * n, 0);
	iota(c.begin(), c.end(), 0);
	sort(c.begin(), c.end(), [&](int i, int j) {
		if (v[i] != v[j]) return v[i] < v[j];
		return i < j;
	});
	vector dp(2 * n + 2, vector(4, i64(1) << 60));
	auto f = [&](int i, int j) {
		if (j >= 2 * n) return false;
		int a = c[i], b = c[j];
		if (a > b) swap(a, b);
		if (a % 2 == 0 && b == a + 1) return false;
		return true;
	};
	dp[0][0] = 0;
	dp[0][3] = abs(v[c[1]] - v[c[2]]);
	for (int i = 0; i < 2 * n; i++) {
		if (f(i, i + 1)) {
			int cost = abs(v[c[i]] - v[c[i + 1]]);
			dp[i + 2][0] = min(dp[i + 2][0], dp[i][0] + cost);
			dp[i + 3][0] = min(dp[i + 3][0], dp[i][2] + cost);
		}
		if (f(i, i + 2)) {
			int cost = abs(v[c[i]] - v[c[i + 2]]);
			dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + cost);
			dp[i + 3][0] = min(dp[i + 3][0], dp[i][1] + cost);
		}
		if (f(i, i + 3)) {
			int cost = abs(v[c[i]] - v[c[i + 3]]);
			dp[i + 1][2] = min(dp[i + 1][2], dp[i][0] + cost);
			dp[i + 2][1] = min(dp[i + 2][1], dp[i][1] + cost);
			dp[i + 1][3] = min(dp[i + 1][3], dp[i][2] + cost);
			dp[i + 4][0] = min(dp[i + 4][0], dp[i][3] + cost);
		}
	}
	return dp[2 * n][0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(2 * n, 0);
	for (int i = 0; i < 2 * n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}