#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int modadd(int a, int b, int mod) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int modsub(int a, int b, int mod) {
	return a < b ? a - b + mod : a - b;
}

constexpr int modmul(int a, int b, int mod) {
	return i64(a) * b % mod;
}

constexpr int modpow(int x, int n, int mod) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = modmul(ret, x, mod);
		x = modmul(x, x, mod);
	}
	return ret;
}

auto sol = [](int n, int m) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = modmul(fac[i - 1], i, m - 1);
	}
	vector bino(n + 1, vector(n + 1, 0));
	for (int i = 0; i <= n; i++) {
		bino[i][0] = 1;
		bino[i][i] = 1;
		for (int j = 1; j <= i - 1; j++) {
			bino[i][j] = modadd(bino[i - 1][j - 1], bino[i - 1][j], m - 1);
		}
	}
	vector s(n + 1, true);
	int ret = 1;
	for (int p = 2; p <= n; p++) {
		if (!s[p]) continue;
		for (int i = p * p; i <= n; i += p) s[i] = false;
		for (int x = p; x <= n; x *= p) {
			vector dp(n + 1, 0); dp[0] = 1;
			int acc = 1;
			for (int i = 1; i <= n; i++) {
				dp[i] = acc;
				for (int j = x; j <= i; j += x) {
					int val = bino[i - 1][j - 1];
					val = modmul(val, fac[j - 1], m - 1);
					val = modmul(val, dp[i - j], m - 1);
					dp[i] = modsub(dp[i], val, m - 1);
				}
				acc = modmul(acc, i, m - 1);
				acc = modadd(acc, dp[i], m - 1);
			}
			int cnt = modsub(fac[n], dp[n], m - 1);
			ret = modmul(ret, modpow(p, cnt, m), m);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}