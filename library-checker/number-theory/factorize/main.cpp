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
	if (n < 2 || n % 2 == 0) return n == 2;
	int k = __builtin_ctzll(n - 1);
	i64 d = (n - 1) >> k;
	for (i64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
		i64 p = modpow(a % n, d, n);
		if (p <= 1) continue;
		for (int i = 0; i < k; i++) {
			if (p == n - 1) break;
			p = modmul(p, p, n);
		}
		if (p != n - 1) return false;
	}
	return true;
};

auto pollard = [](i64 n) {
	auto f = [&](i64 x) { return modadd(modmul(x, x, n), 3, n); };
	i64 x = 0, y = 0, t = 30, p = 2, i = 1, q;
	while (t++ % 40 || gcd(p, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if (q = modmul(p, abs(x - y), n)) p = q;
		x = f(x), y = f(f(y));
	}
	return gcd(p, n);
};

auto factor = [](i64 n) {
	vector ret(0, i64(0));
	auto rec = [&](const auto& self, i64 n) -> void {
		if (n == 1) return;
		if (is_prime(n)) {
			ret.push_back(n);
		}
		else {
			i64 x = pollard(n);
			self(self, x);
			self(self, n / x);
		}
	};
	rec(rec, n);
	sort(ret.begin(), ret.end());
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	while (q--) {
		i64 n; cin >> n;
		auto res = factor(n);
		cout << res.size();
		for (i64 x : res) cout << ' ' << x;
		cout << '\n';
	}
}