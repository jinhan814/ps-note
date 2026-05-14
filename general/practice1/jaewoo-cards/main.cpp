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

auto sol = [](int n) {
	vector inv(2 * n + 1, 1);
	for (int i = 1; i <= 2 * n; i++) {
		inv[i] = mul(inv[i - 1], i);
	}
	for (int i = 2 * n, x = pow(inv[i], mod - 2); i >= 1; i--) {
		inv[i] = mul(inv[i - 1], x);
		x = mul(x, i);
	}
	vector dp(n + 1, vector(n + 1, -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == 0) return 0;
		int& ret = dp[i / 2][j];
		if (ret != -1) return ret;
		ret = 0;
		if (j > 0) {
			int res = self(self, i - 2, j - 1) + 1;
			res = mul(res, j);
			res = mul(res, inv[i - j]);
			ret = add(ret, res);
		}
		if (i - 2 * j > 0) {
			int res = self(self, i - 2, j) + 1;
			res = mul(res, i - 2 * j);
			res = mul(res, inv[i - j]);
			res = mul(res, inv[i - j - 1]);
			ret = add(ret, res);
		}
		if (i - 2 * j > 0) {
			int res = self(self, i - 2, j) + 2;
			res = mul(res, i - 2 * j);
			res = mul(res, inv[i - j]);
			res = mul(res, j);
			res = mul(res, inv[i - j - 1]);
			ret = add(ret, res);
		}
		if (i - 2 * j > 2) {
			int res = self(self, i, j + 2) + 1;
			res = mul(res, i - 2 * j);
			res = mul(res, inv[i - j]);
			res = mul(res, i - 2 * j - 2);
			res = mul(res, inv[i - j - 1]);
			ret = add(ret, res);
		}
		return ret;
	};
	return rec(rec, 2 * n, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	cout << sol(n) << '\n';
}