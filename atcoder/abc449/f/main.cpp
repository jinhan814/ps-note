#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct info {
	int mn, cnt;
	info() : mn(0), cnt(0) {}
	info(int a, int b) : mn(a), cnt(b) {}
	info operator+ (const info& x) const {
		if (mn < x.mn) return *this;
		if (mn > x.mn) return x;
		return info(mn, cnt + x.cnt);
	}
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1) {}
	void set(int i, info x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	void update(int l, int r, int x) {
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
			tree[node] = tree[node << 1] + tree[node << 1 | 1];
		};
		rec(rec, 1, 0, sz - 1);
	}
	info query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> info {
			push(node);
			if (node_r < l || r < node_l) return info(1 << 30, 0);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			info r1 = self(self, node << 1, node_l, mid);
			info r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 0, sz - 1);
	}
private:
	int sz;
	vector<info> tree;
	vector<int> lazy;
	void push(int i) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		tree[i].mn += lazy[i];
		lazy[i] = 0;
	}
};

auto sol = [](int n, int m, int a, int b, int k, auto v) {
	if (k == 0) return i64(n - a + 1) * (m - b + 1);
	vector buc(0, array{ 0, 0, 0, 0 });
	vector c(0, 0);
	for (int i = 0; i < k; i++) {
		auto [x, y] = v[i];
		int x1 = max(x - a + 1, 1);
		int x2 = min(x, n - a + 1);
		int y1 = max(y - b + 1, 1);
		int y2 = min(y, m - b + 1);
		buc.push_back(array{ x1, 1, y1, y2 + 1 });
		buc.push_back(array{ x2 + 1, -1, y1, y2 + 1 });
		c.push_back(y1);
		c.push_back(y2 + 1);
	}
	sort(buc.begin(), buc.end());
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	i64 ret = i64(n - a + 1) * (m - b + 1);
	segtree tree(c.size() - 1);
	for (int i = 0; i < c.size() - 1; i++) {
		tree.set(i, info(0, c[i + 1] - c[i]));
	}
	for (int i = 0, j = 0; i < buc.size(); i = j) {
		while (j < buc.size() && buc[i][0] == buc[j][0]) {
			auto [x, d, l, r] = buc[j++];
			l = lower_bound(c.begin(), c.end(), l) - c.begin();
			r = lower_bound(c.begin(), c.end(), r) - c.begin();
			tree.update(l, r - 1, d);
		}
		if (j < buc.size()) {
			info res = tree.query(0, c.size() - 2);
			i64 v1 = buc[j][0] - buc[i][0];
			i64 v2 = c.back() - c[0];
			if (res.mn == 0) v2 -= res.cnt;
			ret -= v1 * v2;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b, k; cin >> n >> m >> a >> b >> k;
	vector v(k, array{ 0, 0 });
	for (int i = 0; i < k; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, a, b, k, v) << '\n';
}