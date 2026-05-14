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

auto sol = [](int n, int m, int k) {
	vector fac(n + k, 1);
	for (int i = 1; i <= n + k - 1; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + k, pow(fac[n + k - 1], mod - 2));
	for (int i = n + k - 1; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	int ret = 0;
	for (int i = 0; i <= min(n, k / (m + 1)); i++) {
		int v1 = bino(n, i);
		if (i % 2 == 1) v1 = mul(v1, mod - 1);
		int v2 = bino(k - (m + 1) * i + n - 1, n - 1);
		ret = add(ret, mul(v1, v2));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	cout << sol(n, m, k) << '\n';
}