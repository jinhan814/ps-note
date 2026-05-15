#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, bool x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] || tree[i << 1 | 1];
	}
	bool query(int i) const {
		return tree[i | sz];
	}
	bool query(int l, int r) const {
		bool ret = false;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret |= tree[l++];
			if (~r & 1) ret |= tree[r--];
		}
		return ret;
	}
	int get_prv(int i) const {
		if (!query(0, i)) return -1;
		i |= sz;
		while (!tree[i]) i = i - 1 >> 1;
		while (i < sz) i = i << 1 | tree[i << 1 | 1];
		return i - sz;
	}
	int get_nxt(int i) const {
		if (!query(i, sz - 1)) return -1;
		i |= sz;
		while (!tree[i]) i = i + 1 >> 1;
		while (i < sz) i = i << 1 | !tree[i << 1];
		return i - sz;
	}
private:
	int sz;
	vector<bool> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	string s; cin >> s;
	segtree tree(n);
	for (int i = 0; i < n; i++) tree.update(i, s[i] & 1);
	while (q--) {
		int op, x; cin >> op >> x;
		if (op == 0) tree.update(x, 1);
		else if (op == 1) tree.update(x, 0);
		else if (op == 2) cout << tree.query(x) << '\n';
		else if (op == 3) cout << tree.get_nxt(x) << '\n';
		else cout << tree.get_prv(x) << '\n';
	}
}