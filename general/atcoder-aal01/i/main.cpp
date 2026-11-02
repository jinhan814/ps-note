#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() : node(0) {}
	node(int x) {
		s1 = x;
		s2 = max(x, 0);
		l1 = l2 = max(x, 0);
		r1 = r2 = max(x, 0);
		mx1 = mx2 = max(x, 0);
	}
	node operator+ (const node& x) const {
		node ret;
		ret.s1 = s1 + x.s1;
		ret.l1 = max(l1, s1 + x.l1);
		ret.r1 = max(x.r1, r1 + x.s1);
		ret.mx1 = max({ mx1, x.mx1, r1 + x.l1 });
		ret.s2 = max({ s2 + x.s1, s1 + x.s2, l1 + x.r1 });
		ret.l2 = max({ l2, l1 + x.mx1, s1 + x.l2, s2 + x.l1 });
		ret.r2 = max({ x.r2, mx1 + x.r1, r2 + x.s1, r1 + x.s2 });
		ret.mx2 = max({ mx2, x.mx2, mx1 + x.mx1, r2 + x.l1, r1 + x.l2 });
		return ret;
	}
	i64 get() const {
		return mx2;
	}
private:
	i64 s1, l1, r1, mx1;
	i64 s2, l2, r2, mx2;
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
	vector ret(0, i64(0));
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
	for (i64 x : res) cout << x << '\n';
}