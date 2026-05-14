#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector dp(1'000 * n + 1, i64(1) << 60);
	dp[0] = 0;
	int acc = 0;
	for (auto [a, b] : v) {
		for (int i = acc; i >= 0; i--) {
			dp[i + b] = min(dp[i + b], dp[i] + a);
		}
		acc += b;
	}
	int ret = 0;
	for (int i = 0; i <= acc; i++) {
		if (dp[i] > m) continue;
		ret = i;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}