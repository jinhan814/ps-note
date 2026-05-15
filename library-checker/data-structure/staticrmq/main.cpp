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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	segtree tree(n);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		tree.update(i, x);
	}
	while (q--) {
		int l, r; cin >> l >> r;
		cout << tree.query(l + 1, r) << '\n';
	}
}