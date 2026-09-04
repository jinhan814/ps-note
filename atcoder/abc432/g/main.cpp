#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;
constexpr int g = 3;

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

auto ntt(auto& f, bool inv) {
	int n = f.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(f[i], f[j]);
	}
	for (int s = 2; s <= n; s <<= 1) {
		int w_n = pow(g, (mod - 1) / s);
		if (inv) w_n = pow(w_n, mod - 2);
		for (int i = 0; i < n; i += s) {
			int w = 1;
			for (int j = 0; j < s / 2; j++) {
				int a = f[i + j], b = f[i + j + s / 2];
				f[i + j] = add(a, mul(w, b));
				f[i + j + s / 2] = sub(a, mul(w, b));
				w = mul(w, w_n);
			}
		}
	}
	if (inv) {
		int inv_n = pow(n, mod - 2);
		for (int i = 0; i < n; i++) f[i] = mul(f[i], inv_n);
	}
}

auto conv(auto a, auto b) {
	int n = a.size() + b.size() - 1;
	int m = 1 << (__lg(n - 1 | 1) + 1);
	a.resize(m);
	b.resize(m);
	ntt(a, false);
	ntt(b, false);
	for (int i = 0; i < m; i++) a[i] = mul(a[i], b[i]);
	ntt(a, true);
	a.resize(n);
	return a;
}

auto sol = [](int n, int m, auto a, auto b) {
	int sz = 500'000;
	vector fac(sz + 1, 1);
	for (int i = 1; i <= sz; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(sz + 1, pow(fac[sz], mod - 2));
	for (int i = sz; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	vector c1(sz + 1, 0);
	vector c2(sz + 1, 0);
	for (int i = 0; i < n; i++) c1[a[i]]++;
	for (int i = 0; i < m; i++) c2[b[i]]++;
	vector c(sz + 1, 0);
	for (int i = 0; i <= sz; i++) c[i] = mul(c2[i], inv[i]);
	c = conv(c, inv);
	int ret = 0;
	for (int i = 1; i <= sz; i++) {
		int val = mul(mul(c1[i], fac[i]), c[i]);
		ret = add(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}