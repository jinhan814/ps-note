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
	segtree(int n) : sz(n), tree(1, array{ 0, -1, -1 }), lazy(1, array{ 1, 0 }) {}
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
			self(self, tree[node][1], node_l, mid);
			self(self, tree[node][2], mid + 1, node_r);
			tree[node][0] = add(tree[tree[node][1]][0], tree[tree[node][2]][0]);
		};
		rec(rec, 0, 0, sz - 1);
	}
	int query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return 0;
			if (l <= node_l && node_r <= r) return tree[node][0];
			int mid = (node_l + node_r) >> 1;
			int r1 = self(self, tree[node][1], node_l, mid);
			int r2 = self(self, tree[node][2], mid + 1, node_r);
			return add(r1, r2);
		};
		return rec(rec, 0, 0, sz - 1);
	}
private:
	int sz;
	vector<array<int, 3>> tree;
	vector<array<int, 2>> lazy;
	void push(int i, int l, int r) {
		if (l != r) {
			if (tree[i][1] == -1) {
				tree.push_back(array{ 0, -1, -1 });
				lazy.push_back(array{ 1, 0 });
				tree[i][1] = tree.size() - 1;
			}
			if (tree[i][2] == -1) {
				tree.push_back(array{ 0, -1, -1 });
				lazy.push_back(array{ 1, 0 });
				tree[i][2] = tree.size() - 1;
			}
			lazy[tree[i][1]][0] = mul(lazy[tree[i][1]][0], lazy[i][0]);
			lazy[tree[i][1]][1] = mul(lazy[tree[i][1]][1], lazy[i][0]);
			lazy[tree[i][1]][1] = add(lazy[tree[i][1]][1], lazy[i][1]);
			lazy[tree[i][2]][0] = mul(lazy[tree[i][2]][0], lazy[i][0]);
			lazy[tree[i][2]][1] = mul(lazy[tree[i][2]][1], lazy[i][0]);
			lazy[tree[i][2]][1] = add(lazy[tree[i][2]][1], lazy[i][1]);
		}
		tree[i][0] = mul(tree[i][0], lazy[i][0]);
		tree[i][0] = add(tree[i][0], mul(lazy[i][1], r - l + 1));
		lazy[i] = array{ 1, 0 };
	}
};

auto sol = [](int n, int q, auto qs) {
	segtree tree(n);
	vector ret(0, 0);
	for (auto [op, a, b, c, d] : qs) {
		if (op == 0) tree.update(a, b - 1, c, d);
		else ret.push_back(tree.query(a, b - 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0, 0, 0, 0 });
	for (auto& [op, a, b, c, d] : qs) {
		cin >> op >> a >> b;
		if (op == 0) cin >> c >> d;
	}
	auto res = sol(n, q, qs);
	for (int x : res) cout << x << '\n';
}