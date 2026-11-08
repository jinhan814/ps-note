#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) p[b] = a;
	}
private:
	vector<int> p;
};

struct node {
	node() : sz(-1) {}
	node(string s) : sz(s.size()), l(s), r(s), v(2 * sz) {
		for (int i = 0, j = 0; i < sz; i = j) {
			while (j < sz && s[i] == s[j]) j++;
			for (int k = i; k < j; k++) v[k] = v[k + sz] = i;
		}
	}
	node operator+ (const node& x) const {
		if (sz == -1) return x;
		if (x.sz == -1) return *this;
		union_find uf(4 * sz);
		for (int i = 0; i < sz; i++) {
			if (r[i] != x.l[i]) continue;
			uf.merge(v[i + sz], x.v[i] + 2 * sz);
		}
		node ret;
		ret.sz = sz;
		ret.l = l;
		ret.r = x.r;
		ret.v.resize(2 * sz);
		for (int i = 0; i < sz; i++) {
			ret.v[i] = uf.find(v[i]);
			ret.v[i + sz] = uf.find(x.v[i + sz] + 2 * sz);
		}
		ret.norm();
		return ret;
	}
	int get(int i) const {
		return v[i];
	}
private:
	int sz;
	string l, r;
	vector<int> v;
	void norm() {
		vector c(4 * sz, -1);
		for (int i = 0, p = 0; i < 2 * sz; i++) {
			if (c[v[i]] != -1) continue;
			c[v[i]] = p++;
		}
		for (int i = 0; i < 2 * sz; i++) {
			v[i] = c[v[i]];
		}
	}
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, string s) {
		tree[i |= sz] = node(s);
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node res_l, res_r;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return res_l + res_r;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int m, int q, auto v, auto qs) {
	segtree tree(n);
	for (int i = 0; i < n; i++) tree.update(i, v[i]);
	auto calc = [&](int x1, int y1, int x2, int y2) {
		if (x1 > x2) swap(x1, x2), swap(y1, y2);
		auto res_l = tree.query(0, x1);
		auto res_m = tree.query(x1, x2);
		auto res_r = tree.query(x2, n - 1);
		union_find uf(6 * m);
		for (int i = 0; i < m; i++) {
			uf.merge(res_m.get(i), res_l.get(i + m) + 2 * m);
			uf.merge(res_m.get(i + m), res_r.get(i) + 4 * m);
		}
		return uf.find(res_m.get(y1)) == uf.find(res_m.get(y2 + m));
	};
	vector ret(0, false);
	for (auto [op, a, b, c, d, s] : qs) {
		if (op == 1) tree.update(a, s);
		else ret.push_back(calc(a, b, c, d));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector v(n, string{});
	vector qs(q, tuple(0, 0, 0, 0, 0, string{}));
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [op, a, b, c, d, s] : qs) {
		cin >> op;
		if (op == 1) cin >> a >> s, --a;
		else cin >> a >> b >> c >> d, --a, --b, --c, --d;
	}
	auto res = sol(n, m, q, v, qs);
	for (bool x : res) cout << (x ? "Yes" : "No") << '\n';
}