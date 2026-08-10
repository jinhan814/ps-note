#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, string s) {
	if (s[0] != 'o' || s[n - 1] != 'o') return 0;
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector dp(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		dp[i] = fac[i];
		for (int j = 2; j <= i - 1; j++) {
			dp[i] = sub(dp[i], mul(dp[j], fac[i - j + 1]));
		}
	}
	int ret = 1;
	for (int i = 1, x = 0; i < n; i++) {
		if (s[i] == 'x') x++;
		else ret = mul(ret, dp[x + 2]), x = 0;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}