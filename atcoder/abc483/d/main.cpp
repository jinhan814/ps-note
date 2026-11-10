#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector dp(n + 1, array{ i64(0), i64(0) });
	for (int i = n - 1; i >= 0; i--) {
		dp[i][0] = min(i64(0), v[i] + dp[i + 1][0]);
		dp[i][1] = max(i64(0), v[i] + dp[i + 1][1]);
	}
	i64 ret = dp[0][1] - dp[0][0] + 1;
	i64 x = 0, mn = 0, mx = 0;
	for (int i = 0; i < n; i++) {
		i64 v1 = min(mn, x - v[i] + dp[i + 1][0]);
		i64 v2 = max(mx, x - v[i] + dp[i + 1][1]);
		ret = max(ret, v2 - v1 + 1);
		x += v[i];
		mn = min(mn, x);
		mx = max(mx, x);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}