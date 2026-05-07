#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector dp(n + 1, i64(1));
	for (int i = 2; i <= 40; i++) {
		dp[i] = 2 * dp[i - 1];
		if (i >= 3) dp[i] += dp[i - 3];
	}
	cout << dp[n] << '\n';
}