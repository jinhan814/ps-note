#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 val = 0;
	for (int i = 0; i < n; i++) val += v[i];
	val /= m;
	vector dp(1 << n, 0);
	for (int mask = 1; mask < 1 << n; mask++) {
		i64 acc = 0;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			dp[mask] = max(dp[mask], dp[mask ^ 1 << i]);
			acc += v[i];
		}
		if (acc % val == 0) dp[mask]++;
	}
	return m - dp.back();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}