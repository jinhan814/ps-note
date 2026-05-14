#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() : l(0), r(0), s(0), mx(0), flag(true) {}
	node(i64 x) : l(x), r(x), s(x), mx(x), flag(false) {}
	node operator+ (const node& x) const {
		if (flag) return x;
		if (x.flag) return *this;
		node ret;
		ret.l = max(l, s + x.l);
		ret.r = max(r + x.s, x.r);
		ret.s = s + x.s;
		ret.mx = max({ mx, x.mx, r + x.l });
		ret.flag = false;
		return ret;
	}
	i64 get() const {
		return mx;
	}
private:
	i64 l, r, s, mx;
	bool flag;
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
	i64 acc = 0;
	segtree tree(n);
	for (int i = 1; i <= n; i++) {
		acc += v[i];
		tree.update(i, node(v[i] > 0 ? v[i] : -1));
	}
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		acc += b - v[a];
		v[a] = b;
		tree.update(a, v[a] > 0 ? v[a] : -1);
		ret[i] = acc - max(tree.query(1, n).get(), i64(0));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}