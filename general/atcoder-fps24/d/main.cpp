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

auto sol = [](int n, int m) {
	int sz = max((n + m - 1) / 2, n);
	vector fac(sz + 1, 1);
	for (int i = 1; i <= sz; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(sz + 1, pow(fac[sz], mod - 2));
	for (int i = sz; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	int ret = 0;
	for (int i = 0; i <= m - n + 1; i++) {
		int lim = (m - n - i + 1) / 2;
		ret = add(ret, bino(n + lim - 1, lim));
	}
	ret = mul(ret, fac[n]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}