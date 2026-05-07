#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector dp(max(n, 3), i64(0));
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++) {
		dp[i] =	2 * dp[i - 1] + dp[i - 3];
	}
	cout << dp[n] << '\n';
}