#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

struct node {
	node() : a(1), b(0) {}
	node(int a, int b) : a(a), b(b) {}
	node operator+(const node& x) const {
		node ret;
		ret.a = mul(a, x.a);
		ret.b = add(mul(b, x.a), x.b);
		return ret;
	}
	int query(int x) const {
		return add(mul(a, x), b);
	}
private:
	int a, b;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		tree[i |= sz] = x;
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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	segtree tree(n);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		tree.update(i, node(a, b));
	}
	while (q--) {
		int op, a, b, c; cin >> op >> a >> b >> c;
		if (op == 0) tree.update(a, node(b, c));
		else cout << tree.query(a, b - 1).query(c) << '\n';
	}
}