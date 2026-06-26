#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, int m, int k) {
	vector dp(n + 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= k; i++) {
		for (int x = i; x <= n; x++) {
			dp[x] = add(dp[x], dp[x - i]);
		}
	}
	vector ret(m - k + 2, 0);
	ret[1] = dp[n];
	for (int i = k + 1; i <= m; i++) {
		for (int x = n; x >= i - k; x--) {
			dp[x] = sub(dp[x], dp[x - (i - k)]);
		}
		for (int x = i; x <= n; x++) {
			dp[x] = add(dp[x], dp[x - i]);
		}
		ret[i - k + 1] = dp[n];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	auto res = sol(n, m, k);
	for (int i = 1; i <= m - k + 1; i++) cout << res[i] << '\n';
}