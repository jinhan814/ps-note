#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1, -1) {}
	void update(int l, int r, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = x;
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = tree[node << 1] + tree[node << 1 | 1];
		};
		rec(rec, 1, 1, sz);
	}
	i64 query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return i64(0);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			i64 r1 = self(self, node << 1, node_l, mid);
			i64 r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<i64> tree;
	vector<int> lazy;
	void push(int i, int l, int r) {
		if (lazy[i] == -1) return;
		if (i < sz) {
			lazy[i << 1] = lazy[i];
			lazy[i << 1 | 1] = lazy[i];
		}
		tree[i] = i64(r - l + 1) * lazy[i];
		lazy[i] = -1;
	}
};

auto sol = [](int n, auto v) {
	vector buc(n + 1, vector(1, 0));
	for (int i = 1; i <= n; i++) buc[v[i]].push_back(i);
	for (int i = 0; i <= n; i++) buc[i].push_back(n + 1);
	segtree tree(n + 1);
	for (int i = 1; i <= n + 1; i++) tree.update(i, i, n + 1 - i);
	i64 ret = 0;
	for (int x = 0; x <= n - 1; x++) {
		for (int i = 1; i < buc[x].size(); i++) {
			int l = buc[x][i - 1];
			int r = buc[x][i];
			int lo = l, hi = r + 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				if (tree.query(mid, mid) >= n + 1 - r) lo = mid;
				else hi = mid;
			}
			tree.update(l + 1, lo, n + 1 - r);
		}
		ret += tree.query(1, n);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}