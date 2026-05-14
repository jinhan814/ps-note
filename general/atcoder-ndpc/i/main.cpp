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

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](int n, int a, int b, auto v) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) {
		inv[i - 1] = mul(inv[i], i);
	}
	auto bino = [&](int n, int k) {
		if (k < 0 || k > n) return 0;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	sort(v.begin(), v.end(), greater{});
	vector c(0, 0);
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		c.push_back(j - i);
	}
	vector dp(a + 1, vector(b + 1, 0));
	dp[1][1] = 1;
	int acc = c[0];
	for (int iter = 1; iter < c.size(); iter++) {
		int x = c[iter];
		int v1 = bino(acc + x - 2, x);
		int v2 = bino(acc + x - 2, x - 1);
		int v3 = bino(acc + x - 2, x - 2);
		for (int i = a; i >= 1; i--) {
			for (int j = b; j >= 1; j--) {
				if (dp[i][j] == 0) continue;
				if (i + 1 <= a) {
					dp[i + 1][j] = add(dp[i + 1][j], mul(dp[i][j], v2));
				}
				if (j + 1 <= b) {
					dp[i][j + 1] = add(dp[i][j + 1], mul(dp[i][j], v2));
				}
				if (i + 1 <= a && j + 1 <= b) {
					dp[i + 1][j + 1] = add(dp[i + 1][j + 1], mul(dp[i][j], v3));
				}
				dp[i][j] = mul(dp[i][j], v1);
			}
		}
		acc += x;
	}
	return dp[a][b];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, a, b, v) << '\n';
}