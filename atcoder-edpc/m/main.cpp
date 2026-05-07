#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, int k, auto v) {
	vector dp(k + 1, 0);
	dp[0] = 1;
	for (int x : v) {
		for (int i = k - x - 1; i >= 0; i--) {
			dp[i + x + 1] = sub(dp[i + x + 1], dp[i]);
		}
		for (int i = 1; i <= k; i++) {
			dp[i] = add(dp[i], dp[i - 1]);
		}
	}
	return dp[k];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}