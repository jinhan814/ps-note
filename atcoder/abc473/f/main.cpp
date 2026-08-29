#include <bits/stdc++.h>
using namespace std;

struct node {
	node() : mn(0), acc(0) {}
	node(char c) : mn(c == 'A' ? 1 : -1), acc(c == 'A' ? 1 : -1) {}
	node operator+ (const node& x) const {
		node ret;
		ret.mn = min(mn, acc + x.mn);
		ret.acc = acc + x.acc;
		return ret;
	}
	bool operator() () const {
		return mn >= 0;
	}
private:
	int mn, acc;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, char c) {
		tree[i |= sz] = node(c);
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	bool query(int l, int r) const {
		node res_l, res_r;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return (res_l + res_r)();
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int q, string s, auto qs) {
	segtree tree(n);
	for (int i = 0; i < n; i++) {
		tree.update(i, s[i]);
	}
	vector ret(0, false);
	for (auto [op, a, b] : qs) {
		if (op == 1) tree.update(a - 1, b);
		else ret.push_back(tree.query(a - 1, b - 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	int q; cin >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op == 1) { char c; cin >> c; b = c; }
		else cin >> b;
	}
	auto res = sol(n, q, s, qs);
	for (bool x : res) cout << (x ? "Yes" : "No") << '\n';
}