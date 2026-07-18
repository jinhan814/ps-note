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
			tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 0, sz - 1);
	}
	i64 query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> i64 {
			push(node);
			if (node_r < l || r < node_l) return -(i64(1) << 60);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			i64 r1 = self(self, node << 1, node_l, mid);
			i64 r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return max(r1, r2);
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

auto sol = [](int n, int q, auto a, auto b, auto qs) {
	vector c(b.begin() + 1, b.end());
	for (int i = 0; i < q; i++) {
		if (qs[i][0] != 2) continue;
		c.push_back(qs[i][2]);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector cnt(c.size(), 0);
	segtree tree(c.size());
	for (int i = 1; i <= n; i++) {
		int p = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
		tree.update(0, p, a[i]);
		if (++cnt[p] == 1) tree.update(p, p, c[p]);
	}
	vector ret(q, i64(0));
	for (int iter = 0; iter < q; iter++) {
		auto [op, i, x] = qs[iter];
		if (op == 1) {
			int p = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
			tree.update(0, p, x - a[i]);
			a[i] = x;
		}
		else {
			int p1 = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
			int p2 = lower_bound(c.begin(), c.end(), x) - c.begin();
			tree.update(0, p1, -a[i]);
			tree.update(0, p2, a[i]);
			if (--cnt[p1] == 0) tree.update(p1, p1, -c[p1]);
			if (++cnt[p2] == 1) tree.update(p2, p2, c[p2]);
			b[i] = x;
		}
		ret[iter] = tree.query(0, c.size() - 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector a(n + 1, 0);
	vector b(n + 1, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (auto& [op, i, x] : qs) cin >> op >> i >> x;
	auto res = sol(n, q, a, b, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}