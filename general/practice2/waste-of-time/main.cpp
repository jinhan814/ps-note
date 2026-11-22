#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(n + 1, -1); dp[1] = 0;
	for (int i = 1; i <= n - 1; i++) {
		if (dp[i] == -1) continue;
		int j = i + v[i];
		if (j > n) continue;
		dp[j] = max(dp[j], dp[i] + 1);
	}
	for (int i = n - 1; i >= 1; i--) {
		if (dp[i] == -1) continue;
		int j = i - v[i];
		if (j < 1) continue;
		dp[j] = max(dp[j], dp[i] + 1);
	}
	for (int i = 1; i <= n - 1; i++) {
		if (dp[i] == -1) continue;
		int j = i + v[i];
		if (j > n) continue;
		dp[j] = max(dp[j], dp[i] + 1);
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}