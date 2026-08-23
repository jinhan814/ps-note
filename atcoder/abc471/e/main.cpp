#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
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

auto sol = [](int n, int k, auto v) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	int ret = 0, acc = 0;
	for (int i = 0; i < n; i++) {
		int v1 = mul(v[i], v[i]);
		int v2 = bino(n - 1, k - 1);
		ret = add(ret, mul(v1, v2));
		acc = add(acc, v[i]);
	}
	if (k >= 2) {
		int val = 0;
		for (int i = 0; i < n; i++) {
			int x = mul(v[i], sub(acc, v[i]));
			val = add(val, x);
		}
		val = mul(val, bino(n - 2, k - 2));
		ret = add(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}