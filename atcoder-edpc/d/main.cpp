#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector dp(m + 1, i64(0));
	for (auto [a, b] : v) {
		for (int i = m; i >= a; i--) {
			dp[i] = max(dp[i], dp[i - a] + b);
		}
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}