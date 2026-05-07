#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, string s) {
	vector dp(n, 0);
	dp[0] = 1;
	for (int i = 0; i < n - 1; i++) {
		if (s[i] == '<') {
			for (int j = 1; j <= i; j++) dp[j] = add(dp[j], dp[j - 1]);
			for (int j = i; j >= 0; j--) dp[j + 1] = dp[j];
			dp[0] = 0;
		}
		else {
			for (int j = i; j >= 1; j--) dp[j - 1] = add(dp[j - 1], dp[j]);
		}
	}
	int ret = 0;
	for (int i = 0; i < n; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}