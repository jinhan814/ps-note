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

auto sol = [](int n, i64 m, auto v) {
	vector q{ 1, mod - 1 };
	for (int x : v) {
		vector c(x + 1, 0);
		c[0] = 1;
		c[x] = mod - 1;
		q = conv(q, c);
	}
	vector p(q.size() - 1, 0);
	p[0] = 1;
	for (; m; m >>= 1) {
		auto c = q;
		for (int i = 1; i < q.size(); i += 2) c[i] = sub(0, q[i]);
		auto np = conv(p, c);
		auto nq = conv(q, c);
		for (int i = 0; i < p.size(); i++) p[i] = np[i << 1 | (m & 1)];
		for (int i = 0; i < q.size(); i++) q[i] = nq[i << 1];
	}
	return p[0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 m; cin >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}