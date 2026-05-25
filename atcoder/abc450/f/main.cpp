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

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1, array{ 1, 0 }) {}
	void update(int l, int r, int a, int b) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = array{ a, b };
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = add(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 1, sz);
	}
	int query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return 0;
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			int r1 = self(self, node << 1, node_l, mid);
			int r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return add(r1, r2);
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<int> tree;
	vector<array<int, 2>> lazy;
	void push(int i, int l, int r) {
		if (i < sz) {
			lazy[i << 1][0] = mul(lazy[i << 1][0], lazy[i][0]);
			lazy[i << 1][1] = mul(lazy[i << 1][1], lazy[i][0]);
			lazy[i << 1][1] = add(lazy[i << 1][1], lazy[i][1]);
			lazy[i << 1 | 1][0] = mul(lazy[i << 1 | 1][0], lazy[i][0]);
			lazy[i << 1 | 1][1] = mul(lazy[i << 1 | 1][1], lazy[i][0]);
			lazy[i << 1 | 1][1] = add(lazy[i << 1 | 1][1], lazy[i][1]);
		}
		tree[i] = mul(tree[i], lazy[i][0]);
		tree[i] = add(tree[i], mul(lazy[i][1], r - l + 1));
		lazy[i] = array{ 1, 0 };
	}
};

auto sol = [](int n, int m, auto e) {
	sort(e.begin(), e.end());
	segtree tree(n);
	tree.update(1, 1, 0, 1);
	for (auto [a, b] : e) {
		tree.update(b, b, 1, tree.query(a, b));
		if (b < n) tree.update(b + 1, n, 2, 0);
	}
	return tree.query(n, n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0 });
	for (auto& [a, b] : e) cin >> a >> b;
	cout << sol(n, m, e) << '\n';
}