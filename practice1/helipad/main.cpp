#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector dp(447, vector(50'001, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= 446; i++) {
		for (int j = 0; j <= 50'000; j++) {
			if (j > i * (i - 1) / 2) break;
			dp[i][j] = dp[i - 1][j];
		}
		for (int j = 0; i + j <= 50'000; j++) {
			if (j > i * (i - 1) / 2) break;
			dp[i][i + j] = add(dp[i][i + j], dp[i - 1][j]);
		}
	}
	for (int i = 1; i <= 446; i++) {
		for (int j = 1; j <= 50'000; j++) {
			dp[i][j] = add(dp[i][j], dp[i][j - 1]);
		}
	}
	auto calc = [&](int a, int b) {
		int ret = 0;
		for (int i = 1; i <= 446; i++) {
			int l = max(0, i * (i + 1) / 2 - b);
			int r = min(a, i * (i + 1) / 2);
			if (l > r) break;
			ret = add(ret, dp[i][r]);
			if (l > 0) ret = sub(ret, dp[i][l - 1]);
		}
		return ret;
	};
	int tc; cin >> tc;
	while (tc--) {
		int a, b; cin >> a >> b;
		cout << calc(a, b) << '\n';
	}
}