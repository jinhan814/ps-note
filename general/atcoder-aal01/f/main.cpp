#include <bits/stdc++.h>
using namespace std;

struct node {
	node() : sz(0), vl(-1), vr(-1), l(0), r(0), mx(0) {}
	node(int x) : sz(1), vl(x), vr(x), l(1), r(1), mx(1) {}
	node operator+ (const node& x) const {
		node ret;
		ret.sz = sz + x.sz;
		ret.vl = vl;
		ret.vr = x.vr;
		ret.l = mx == sz && vl == x.vl ? sz + x.l : l;
		ret.r = x.mx == x.sz && vr == x.vr ? r + x.sz : x.r;
		ret.mx = max(mx, x.mx);
		if (vr == x.vl) ret.mx = max(ret.mx, r + x.l);
		return ret;
	}
	int get() const {
		return mx;
	}
private:
	int sz, vl, vr, l, r, mx;
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

auto sol = [](int n, int q, auto v, auto qs) {
	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update(i, node(v[i]));
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) tree.update(a, b);
		else ret.push_back(tree.query(a, b).get());
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, tuple(0, 0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}