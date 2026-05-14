#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector dp(n, 0);
	for (int i = 1; i < n; i++) {
		dp[i] = 1 << 30;
		for (int j = 1; j <= k; j++) {
			if (i - j < 0) break;
			dp[i] = min(dp[i], dp[i - j] + abs(v[i] - v[i - j]));
		}
	}
	return dp[n - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}