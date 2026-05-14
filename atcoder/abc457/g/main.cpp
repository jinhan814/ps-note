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
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1), lazy(sz << 1, 1) {}
	void update_mul(int l, int r, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node);
			if (r < node_l || node_r < l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = mul(lazy[node], x);
				push(node);
				return;
			}
			int mid = (node_l + node_r) / 2;
			self(self, 2 * node, node_l, mid);
			self(self, 2 * node + 1, mid + 1, node_r);
		};
		rec(rec, 1, 1, sz);
	}
	void update_add(int i, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node);
			if (node_l == node_r) {
				tree[node] = add(tree[node], x);
				return;
			}
			int mid = (node_l + node_r) / 2;
			if (i <= mid) self(self, 2 * node, node_l, mid);
			else self(self, 2 * node + 1, mid + 1, node_r);
		};
		rec(rec, 1, 1, sz);
	}
	int query(int i) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node);
			if (node_l == node_r) return tree[node];
			int mid = (node_l + node_r) / 2;
			if (i <= mid) return self(self, 2 * node, node_l, mid);
			else return self(self, 2 * node + 1, mid + 1, node_r);
		};
		return rec(rec, 1, 1, sz);
	}
private:
	int sz;
	vector<int> tree;
	vector<int> lazy;
	void push(int i) {
		if (i < sz) {
			lazy[2 * i] = mul(lazy[2 * i], lazy[i]);
			lazy[2 * i + 1] = mul(lazy[2 * i + 1], lazy[i]);
		}
		tree[i] = mul(tree[i], lazy[i]);
		lazy[i] = 1;
	}
};

auto sol = [](int n, auto v) {
	segtree tree(n);
	for (int i = 1; i <= n; i++) tree.update_add(i, 1);
	for (int i = 2; i <= n; i++) {
		int j = v[i - 1] + i - 1;
		int v1 = 0;
		int v2 = 0;
		if (i <= n - 1 && v[i - 1] == v[i]) v1 = n - i;
		if (j <= n) v2 = add(tree.query(i - 1), tree.query(j));
		tree.update_mul(1, n, v1);
		if (j <= n) tree.update_add(j, v2);
	}
	return tree.query(n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 1; i <= n - 1; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}