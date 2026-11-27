#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector dp(m + 1, bitset<16'001>{});
	dp[0][0] = 1;
	for (int x : v) {
		for (int i = m; i >= 1; i--) {
			dp[i] |= dp[i - 1] << x;
		}
	}
	int ret = 0;
	for (int x = 0; x <= 16'000; x++) {
		if (!dp[m][x]) continue;
		ret = max(ret, x * (m * k - x));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i] >> v[i];
	cout << sol(n, m, k, v) << '\n';
}