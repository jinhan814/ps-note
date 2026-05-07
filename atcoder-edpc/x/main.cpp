#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [&](auto a, auto b) {
		return a[0] + a[1] < b[0] + b[1];
	});
	vector dp(10'001, i64(0));
	for (auto [a, b, c] : v) {
		for (int i = b; i >= 0; i--) {
			if (i + a > 10'000) continue;
			dp[i + a] = max(dp[i + a], dp[i] + c);
		}
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [a, b, c] : v) cin >> a >> b >> c;
	cout << sol(n, v) << '\n';
}