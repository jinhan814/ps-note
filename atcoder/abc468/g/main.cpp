#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, string s) {
	if (s[0] != 'o' || s[n - 1] != 'o') return 0;
	vector dp(n + 1, 1);
	for (int i = 2; i <= n; i++) {
		dp[i] = mul(i - 2, dp[i - 1]);
		for (int j = 0; j <= i - 1; j++) {
			int val = mul(dp[j], dp[i - j - 1]);
			dp[i] = add(dp[i], mul(2, val));
		}
	}
	int ret = 1;
	for (int i = 1, x = 0; i < n; i++) {
		if (s[i] == 'x') x++;
		else ret = mul(ret, mul(2, dp[x])), x = 0;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}