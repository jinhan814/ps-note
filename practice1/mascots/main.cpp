#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

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

int bino(int n, int k) {
	if (k > n - k) k = n - k;
	int a = 1, b = 1;
	for (int i = 0; i < k; i++) {
		a = mul(a, n - i);
		b = mul(b, i + 1);
	}
	return mul(a, pow(b, mod - 2));
}

int calc(int n, int m, int a, int b) {
	vector fac(max(n, m) + 1, 1);
	for (int i = 1; i <= max(n, m); i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector dp(n - a + 1, vector(m - b + 1, -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == n && j == m) return 1;
		int& ret = dp[i - a][j - b];
		if (ret != -1) return ret;
		ret = 0;
		if (i < n) ret = add(ret, mul(self(self, i + 1, j), fac[j]));
		if (j < m) ret = add(ret, mul(self(self, i, j + 1), fac[i]));
		return ret;
	};
	return rec(rec, a, b);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	int mn_x = 1 << 30, mx_x = -(1 << 30);
	int mn_y = 1 << 30, mx_y = -(1 << 30);
	for (int i = 0; i < k; i++) {
		int x, y; cin >> x >> y;
		mn_x = min(mn_x, x);
		mx_x = max(mx_x, x);
		mn_y = min(mn_y, y);
		mx_y = max(mx_y, y);
	}
	int a = mx_x - mn_x + 1;
	int b = mx_y - mn_y + 1;
	int res = calc(n, m, a, b);
	res = mul(res, bino(n - a, mn_x - 1));
	res = mul(res, bino(m - b, mn_y - 1));
	for (int i = 1; i <= a * b - k; i++) res = mul(res, i);
	cout << res << '\n';
}