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
	node(mint x) : v1(x), v2(x * x), v3(x * x * x), v4(x * x * x * x) {}
	node operator+ (const node& x) const {
		node ret;
		ret.v1 = v1 + x.v1;
		ret.v2 = v2 + x.v2;
		ret.v3 = v3 + x.v3;
		ret.v4 = v4 + x.v4;
		return ret;
	}
	void push(mint x, mint sz) {
		v4 += mint(4) * v3 * x + mint(6) * v2 * x * x + mint(4) * v1 * x * x * x + sz * x * x * x * x;
		v3 += mint(3) * v2 * x + mint(3) * v1 * x * x + sz * x * x * x;
		v2 += mint(2) * v1 * x + sz * x * x;
		v1 += sz * x;
	}
	mint get(int k) {
		if (k == 1) return v1;
		if (k == 2) return v2;
		if (k == 3) return v3;
		return v4;
	}
private:
	mint v1, v2, v3, v4;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, mint x) {
		auto rec = [&](const auto& self, int i, int i_l, int i_r) {
			push(i, i_l, i_r);
			if (i_r < l || r < i_l) return;
			if (l <= i_l && i_r <= r) {
				lazy[i] = x;
				push(i, i_l, i_r);
				return;
			}
			int mid = (i_l + i_r) >> 1;
			self(self, i << 1, i_l, mid);
			self(self, i << 1 | 1, mid + 1, i_r);
			tree[i] = tree[i << 1] + tree[i << 1 | 1];
		};
		rec(rec, 1, 1, sz);
	}
	node query(int l, int r) {
		auto rec = [&](const auto& self, int i, int node_l, int node_r) {
			push(i, node_l, node_r);
			if (node_r < l || r < node_l) return node();
			if (l <= node_l && node_r <= r) return tree[i];
			int mid = (node_l + node_r) >> 1;
			node r1 = self(self, i << 1, node_l, mid);
			node r2 = self(self, i << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<node> tree;
	vector<mint> lazy;
	void push(int i, int l, int r) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		tree[i].push(lazy[i], r - l + 1);
		lazy[i] = 0;
	}
};

auto sol = [](int n, int q, auto v, auto qs) {
	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update(i, i, v[i]);
	vector ret(0, mint(0));
	for (auto [op, a, b, c] : qs) {
		if (op == 1) tree.update(a, b, c);
		else ret.push_back(tree.query(a, b).get(c));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, mint(0));
	vector qs(q, tuple(0, 0, 0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b, c] : qs) cin >> op >> a >> b >> c;
	auto res = sol(n, q, v, qs);
	for (mint x : res) cout << x << '\n';
}