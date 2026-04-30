#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1 | 1) + 1), tree(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] += x;
				push(node);
				return;
			}
			int mid = node_l + node_r >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 1, sz);
	}
	int query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node);
			if (node_r < l || r < node_l) return 0;
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = node_l + node_r >> 1;
			int res_l = self(self, node << 1, node_l, mid);
			int res_r = self(self, node << 1 | 1, mid + 1, node_r);
			return max(res_l, res_r);
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<int> tree, lazy;
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
	vector dp(n + 2, 0);
	vector prv(m + 1, n + 1);
	segtree data(n + 1);
	for (int i = n; i >= 1; i--) {
		if (v[i] != 0) data.update(i + 1, prv[v[i]], 1), prv[v[i]] = i;
		dp[i] = data.query(min(i + (m + 1) / 2, n + 1), n + 1);
		data.update(i, i, dp[i]);
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) ret = max(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}