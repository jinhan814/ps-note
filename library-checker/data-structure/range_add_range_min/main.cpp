#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, i64 x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = x;
				push(node);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 0, sz - 1);
	}
	i64 query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> i64 {
			push(node);
			if (node_r < l || r < node_l) return i64(1) << 60;
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			i64 r1 = self(self, node << 1, node_l, mid);
			i64 r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return min(r1, r2);
		};
		return rec(rec, 1, 0, sz - 1);
	}
private:
	int sz;
	vector<i64> tree;
	vector<i64> lazy;
	void push(int i) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		tree[i] += lazy[i];
		lazy[i] = 0;
	}
};

auto sol = [](int n, int q, auto v, auto qs) {
	segtree tree(n);
	for (int i = 0; i < n; i++) tree.update(i, i, v[i]);
	vector ret(0, i64(0));
	for (auto [op, a, b, c] : qs) {
		if (op == 0) tree.update(a, b - 1, c);
		else ret.push_back(tree.query(a, b - 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [op, a, b, c] : qs) {
		cin >> op >> a >> b;
		if (op == 0) cin >> c;
	}
	auto res = sol(n, q, v, qs);
	for (i64 x : res) cout << x << '\n';
}