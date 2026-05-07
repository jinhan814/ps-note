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
	vector p(n, 10);
	for (int i = 1; i <= n - 1; i++) {
		p[i] = mul(p[i - 1], p[i - 1]);
	}
	vector dp(1 << n, 0);
	for (int i = 0; i < 1 << n; i++) {
		dp[i] = s[i] - 48;
	}
	for (int bit = 0; bit < n; bit++) {
		for (int i = 0; i < 1 << n; i++) {
			if (~i >> bit & 1) continue;
			int j = i ^ 1 << bit;
			int cnt = __builtin_popcount(j & ((1 << bit) - 1));
			dp[i] = add(dp[i], mul(dp[j], p[cnt]));
		}
	}
	i64 ret = 0;
	for (int i = 0; i < 1 << n; i++) ret += dp[i] ^ i;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}