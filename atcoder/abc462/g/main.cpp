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

auto conv = [](auto a, auto b) {
	auto ntt = [&](auto& f, bool inv) {
		const int n = f.size();
		for (int i = 1, j = 0; i < n; i++) {
			int bit = n >> 1;
			for (; j & bit; bit >>= 1) j ^= bit;
			j ^= bit;
			if (i < j) swap(f[i], f[j]);
		}
		for (int s = 2; s <= n; s <<= 1) {
			int w_n = pow(3, (mod - 1) / s);
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
	};
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
};

auto sol = [](int n, auto a, auto b) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector ca(n + 1, 0), cb(n + 1, 0);
	for (int x : a) ca[x]++;
	for (int x : b) cb[x]++;
	auto cmp = [](const auto& a, const auto& b) { return a.size() > b.size(); };
	priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
	for (int x = 1; x <= n; x++) {
		if (min(ca[x], cb[x]) == 0) continue;
		vector c(min(ca[x], cb[x]) + 1, 0);
		c[0] = 1;
		for (int i = 1; i <= min(ca[x], cb[x]); i++) {
			c[i] = fac[i];
			c[i] = mul(c[i], bino(ca[x], i));
			c[i] = mul(c[i], bino(cb[x], i));
		}
		pq.push(c);
	}
	if (pq.empty()) return 1;
	while (pq.size() >= 2) {
		auto p1 = pq.top(); pq.pop();
		auto p2 = pq.top(); pq.pop();
		auto c = conv(p1, p2);
		if (c.size() > n + 1) c.resize(n + 1);
		pq.push(c);
	}
	auto p = pq.top();
	int ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int val = mul(p[i], fac[n - i]);
		if (i % 2 == 0) ret = add(ret, val);
		else ret = sub(ret, val);
	}
	ret = mul(ret, pow(fac[n], mod - 2));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}