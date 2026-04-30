#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() : l(0), r(0), s(0), mx(0), flag(true) {}
	node(i64 x) : l(x), r(x), s(x), mx(x), flag(false) {}
	node operator + (const node& x) const {
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
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1, node(0)) {}
	void update(int i, i64 x) {
		tree[--i |= sz] = node(x);
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	i64 query(int l, int r) const {
		node res_l, res_r;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return (res_l + res_r).get();
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int m, int k, int q, auto qs) {
	vector v(n - k + 1, i64(0));
	segtree tree(n - k);
	for (int i = 1; i <= n - k; i++) {
		v[i] = -m;
		tree.update(i, v[i]);
	}
	vector ret(q, false);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		v[a] += b;
		tree.update(a, v[a]);
		ret[i] = tree.query(1, n - k) <= i64(k) * m;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k, q; cin >> n >> q >> m >> k;
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, m, k, q, qs);
	for (int i = 0; i < q; i++) cout << (res[i] ? "TAK" : "NIE") << '\n';
}