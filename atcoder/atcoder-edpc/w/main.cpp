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
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 0, sz - 1);
	}
	i64 query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> i64 {
			push(node);
			if (node_r < l || r < node_l) return -(i64(1) << 60);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = node_l + node_r >> 1;
			i64 v1 = self(self, node << 1, node_l, mid);
			i64 v2 = self(self, node << 1 | 1, mid + 1, node_r);
			return max(v1, v2);
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

auto sol = [](int n, int m, auto v) {
	vector in(n + 1, vector(0, 0));
	vector out(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		auto [l, r, x] = v[i];
		in[l].push_back(i);
		out[r].push_back(i);
	}
	segtree tree(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int p : in[i]) {
			auto [l, r, x] = v[p];
			tree.update(l, r, -x);
		}
		tree.update(i, i, tree.query(0, i - 1) - tree.query(i, i));
		for (int p : out[i]) {
			auto [l, r, x] = v[p];
			tree.update(l, r, x);
		}
	}
	return tree.query(0, n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0, 0 });
	for (auto& [l, r, x] : v) cin >> l >> r >> x;
	cout << sol(n, m, v) << '\n';
}