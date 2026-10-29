#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1, 1 << 30) {}
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		int ret = 1 << 30;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update(i, v[i]);
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) tree.update(a, b);
		else ret.push_back(tree.query(a, b));
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