#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	vector dp(2 * k + 1, i64(0));
	for (auto [a, b] : v) {
		for (int i = 2 * k; i >= 1; i--) {
			dp[i] = max(dp[i], dp[i - 1]);
			if (i % 2 == 0) dp[i] += a;
			else dp[i] += b;
		}
		dp[0] = dp[0] + a;
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, k, v) << '\n';
}