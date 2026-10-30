#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() : cnt(0), v0(0), v1(0), v2(0) {}
	node(int x) : cnt(0), v0(x == 0), v1(x == 1), v2(x == 2) {}
	node operator+ (const node& x) const {
		node ret;
		ret.cnt = cnt + x.cnt + i64(v1) * x.v0 + i64(v2) * (x.v0 + x.v1);
		ret.v0 = v0 + x.v0;
		ret.v1 = v1 + x.v1;
		ret.v2 = v2 + x.v2;
		return ret;
	}
	i64 get() const {
		return cnt;
	}
private:
	i64 cnt;
	int v0, v1, v2;
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