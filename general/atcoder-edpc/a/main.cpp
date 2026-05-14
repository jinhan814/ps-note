#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(n, 0);
	for (int i = 1; i < n; i++) {
		dp[i] = dp[i - 1] + abs(v[i] - v[i - 1]);
		if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + abs(v[i] - v[i - 2]));
	}
	return dp[n - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}