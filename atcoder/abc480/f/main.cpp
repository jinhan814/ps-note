#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 val = 0;
	for (int i = 0; i < n; i++) val += v[i];
	val /= m;
	vector dp(1 << n, 1 << 30);
	dp[0] = 0;
	for (int mask = 1; mask < 1 << n; mask++) {
		i64 x = 0;
		for (int i = 0; i < n; i++) {
			if (mask >> i & 1) continue;
			x += v[i];
		}
		x %= val;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			int v1 = dp[mask ^ 1 << i];
			int v2 = (v[i] + x - 1) / val;
			dp[mask] = min(dp[mask], v1 + v2);
		}
	}
	return dp.back();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}