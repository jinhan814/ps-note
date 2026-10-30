#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template<int mod>
struct modint {
	constexpr modint() : r(0) {}
	constexpr modint(int x) : r(x % mod) { if (r < 0) r += mod; }
	constexpr modint(i64 x) : r(x % mod) { if (r < 0) r += mod; }
	static modint pow(modint x, i64 n) {
		modint ret = 1;
		for (; n; n >>= 1, x *= x) if (n & 1) ret *= x;
		return ret;
	}
	modint inv() const { return pow(*this, mod - 2); }
	modint operator- () const { return r ? mod - r : 0; }
	modint operator+ (const modint& x) const { return modint(*this) += x; }
	modint operator- (const modint& x) const { return modint(*this) -= x; }
	modint operator* (const modint& x) const { return modint(*this) *= x; }
	modint operator/ (const modint& x) const { return modint(*this) /= x; }
	modint& operator+= (const modint& x) { r = r - mod < -x.r ? r + x.r : r - mod + x.r; return *this; }
	modint& operator-= (const modint& x) { r = r < x.r ? r - x.r + mod : r - x.r; return *this; }
	modint& operator*= (const modint& x) { r = (i64)r * x.r % mod; return *this; }
	modint& operator/= (const modint& x) { return *this *= x.inv(); }
	bool operator== (const modint& x) const { return r == x.r; }
	bool operator!= (const modint& x) const { return r != x.r; }
	operator int() const { return r; }
	friend istream& operator>> (istream& in, modint& x) { i64 t; in >> t; x = modint(t); return in; }
	friend ostream& operator<< (ostream& out, const modint& x) { return out << x.r; }
private:
	int r;
};

using mint = modint<998'244'353>;

struct node {
	node() {}
	node(char c, mint x) {
		if (c == 'R') r = x;
		if (c == 'G') g = x;
		if (c == 'B') b = x;
	}
	node operator+ (const node& x) const {
		node ret;
		ret.r = r + x.r;
		ret.g = g + x.g;
		ret.b = b + x.b;
		ret.rg = rg + x.rg + r * x.g;
		ret.gb = gb + x.gb + g * x.b;
		ret.rgb = rgb + x.rgb + r * x.gb + rg * x.b;
		return ret;
	}
	mint get() const {
		return rgb;
	}
private:
	mint r, g, b, rg, gb, rgb;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node res_l, res_r;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return res_l + res_r;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int q, auto v, string s, auto qs) {
	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update(i, node(s[i - 1], v[i]));
	vector ret(0, mint(0));
	for (auto [op, a, b] : qs) {
		if (op == 1) tree.update(a, node(s[a - 1], b));
		else ret.push_back(tree.query(a, b).get());
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, mint(0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	string s; cin >> s;
	vector qs(q, tuple(0, 0, 0));
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, s, qs);
	for (mint x : res) cout << x << '\n';
}