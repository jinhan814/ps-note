#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'009;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, int m) {
	vector dp(m + 1, 0);
	dp[0] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = m - i; j >= 0; j--) {
			dp[j + i] = sub(dp[j + i], dp[j]);
		}
		for (int j = 1; j <= m; j++) {
			dp[j] = add(dp[j], dp[j - 1]);
		}
	}
	int ret = 0;
	for (int i = m; i >= 0; i -= 2) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}