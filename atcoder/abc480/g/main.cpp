#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1) {}
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
			tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 0, sz - 1);
	}
	int query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node);
			if (node_r < l || r < node_l) return 1 << 30;
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			int r1 = self(self, node << 1, node_l, mid);
			int r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return min(r1, r2);
		};
		return rec(rec, 1, 0, sz - 1);
	}
private:
	int sz;
	vector<int> tree;
	vector<int> lazy;
	void push(int i) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		tree[i] += lazy[i];
		lazy[i] = 0;
	}
};

auto sol = [](int n, auto v) {
	segtree tree(n + 1);
	vector s1(1, 0);
	vector s2(1, 0);
	for (int i = 1; i <= n; i++) {
		while (s1.back() >= 1 && v[s1.back()] <= v[i]) {
			tree.update(s1[s1.size() - 2], s1.back() - 1, -v[s1.back()]);
			s1.pop_back();
		}
		while (s2.back() >= 1 && v[s2.back()] >= v[i]) {
			tree.update(s2[s2.size() - 2], s2.back() - 1, v[s2.back()]);
			s2.pop_back();
		}
		tree.update(s1.back(), i - 1, v[i]);
		s1.push_back(i);
		tree.update(s2.back(), i - 1, -v[i]);
		s2.push_back(i);
		tree.update(i, i, tree.query(0, i - 2));
	}
	return tree.query(n, n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}