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

auto sol = [](int n, int m, int k, auto v) {
	vector fac(n * m + 1, 1);
	for (int i = 1; i <= n * m; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	auto bino = [&](int n, int k) {
		int v1 = fac[n];
		int v2 = mul(fac[k], fac[n - k]);
		return mul(v1, pow(v2, mod - 2));
	};
	vector dp(n + 1, vector(m + 1, -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == n && j == m) return 1;
		int& ret = dp[i][j];
		if (ret != -1) return ret;
		ret = 0;
		if (i < n) ret = add(ret, mul(self(self, i + 1, j), fac[j]));
		if (j < m) ret = add(ret, mul(self(self, i, j + 1), fac[i]));
		return ret;
	};
	int mn_x = 1 << 30, mx_x = -(1 << 30);
	int mn_y = 1 << 30, mx_y = -(1 << 30);
	for (auto [x, y] : v) {
		mn_x = min(mn_x, x);
		mx_x = max(mx_x, x);
		mn_y = min(mn_y, y);
		mx_y = max(mx_y, y);
	}
	int a = mx_x - mn_x + 1;
	int b = mx_y - mn_y + 1;
	int ret = fac[a * b - k];
	ret = mul(ret, rec(rec, a, b));
	ret = mul(ret, bino(n - a, mn_x - 1));
	ret = mul(ret, bino(m - b, mn_y - 1));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, array{ 0, 0 });
	for (int i = 0; i < k; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, k, v) << '\n';
}