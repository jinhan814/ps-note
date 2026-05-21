#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto modadd = [](i64 a, i64 b, i64 mod) {
	return a + b < mod ? a + b : a + b - mod;
};

auto modmul = [](i64 a, i64 b, i64 mod) {
	return i128(a) * b % mod;
};

auto modpow = [](i64 x, i64 n, i64 mod) {
	i64 res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = modmul(res, x, mod);
		x = modmul(x, x, mod);
	}
	return res;
};

auto is_prime = [](i64 n) {
	if (n < 2 || n % 2 == 0 || n % 3 == 0) return n == 2 || n == 3;
	i64 k = __builtin_ctzll(n - 1), d = (n - 1) >> k;
	for (i64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
		i64 p = modpow(a % n, d, n), i = k;
		while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
		if (p != n - 1 && i != k) return false;
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	while (q--) {
		i64 n; cin >> n;
		cout << (is_prime(n) ? "Yes" : "No") << '\n';
	}
}