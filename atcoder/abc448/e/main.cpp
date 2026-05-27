#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto modadd = [](int a, int b, int mod) {
	return a + b < mod ? a + b : a + b - mod;
};

auto modsub = [](int a, int b, int mod) {
	return a < b ? a - b + mod : a - b;
};

auto modmul = [](int a, int b, int mod) {
	return i64(a) * b % mod;
};

auto modpow = [](int x, i64 n, int mod) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = modmul(ret, x, mod);
		x = modmul(x, x, mod);
	}
	return ret;
};

auto sol = [](int n, int m, auto a, auto b) {
	int m1 = 9 * m;
	int m2 = 10'007;
	int ret = 0;
	int acc = 0;
	i64 s = 0;
	for (int i = n - 1; i >= 0; i--) {
		int v1 = a[i] % m1;
		v1 = modmul(v1, modsub(modpow(10 % m1, b[i], m1), 1, m1), m1);
		v1 = modmul(v1, modpow(10 % m1, s, m1), m1);
		v1 /= 9;
		int v2 = a[i] % m2;
		v2 = modmul(v2, modsub(modpow(10 % m2, b[i], m2), 1, m2), m2);
		v2 = modmul(v2, modpow(10 % m2, s, m2), m2);
		v2 = modmul(v2, modpow(9, m2 - 2, m2), m2);
		v2 = modsub(v2, v1, m2);
		v2 = modmul(v2, modpow(m, m2 - 2, m2), m2);
		ret = modadd(ret, v2, m2);
		acc += v1;
		s += b[i];
	}
	ret = modadd(ret, acc / m % m2, m2);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, m, a, b) << '\n';
}