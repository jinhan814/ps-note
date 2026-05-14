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

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), d1(sz << 1), d2(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, mint x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] += x;
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) / 2;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			d1[node] = d1[node << 1] + d1[node << 1 | 1];
			d2[node] = d2[node << 1] + d2[node << 1 | 1];
		};
		rec(rec, 1, 1, sz);
	}
	mint query1(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> mint {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return mint(0);
			if (l <= node_l && node_r <= r) return d1[node];
			int mid = (node_l + node_r) / 2;
			mint r1 = self(self, node << 1, node_l, mid);
			mint r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 1, sz);
	}
	mint query2(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> mint {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return mint(0);
			if (l <= node_l && node_r <= r) return d2[node];
			int mid = (node_l + node_r) / 2;
			mint r1 = self(self, node << 1, node_l, mid);
			mint r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<mint> d1, d2;
	vector<mint> lazy;
	void push(int i, int l, int r) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		d2[i] += mint(2) * d1[i] * lazy[i] + mint(r - l + 1) * lazy[i] * lazy[i];
		d1[i] += mint(r - l + 1) * lazy[i];
		lazy[i] = 0;
	}
};

auto sol = [](int n, int q, auto qs) {
	vector ret(q, mint(0));
	segtree tree(n);
	for (int i = 0; i < q; i++) {
		auto [l, r, x] = qs[i];
		tree.update(l, r, x);
		mint v1 = tree.query1(l, r);
		mint v2 = tree.query2(l, r);
		ret[i] = v1 * v1 - v2;
	}
	mint inv2 = mint(2).inv();
	for (int i = 0; i < q; i++) {
		ret[i] *= inv2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [l, r, x] : qs) cin >> l >> r >> x;
	auto res = sol(n, q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}