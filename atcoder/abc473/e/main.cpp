#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector dp(n + 1, 0);
	map m{ pair(0, 0) };
	for (int i = 1, x = 0; i <= n; i++) {
		x += v[i - 1];
		if (x >= k) x -= k;
		dp[i] = dp[i - 1];
		if (m.count(x)) dp[i] = max(dp[i], m[x] + 1);
		m[x] = dp[i];
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) ret = max(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}