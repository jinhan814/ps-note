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

auto sol = [](int n, int q, auto v, auto qs) {
	vector root(q + 1, 0);
	vector tree(1, array{ 0, -1, -1 });
	vector lazy(1, array{ 1, 0 });
	auto push = [&](int i, int l, int r) {
		if (l != r) {
			if (tree[i][1] == -1) {
				tree.push_back(array{ 0, -1, -1 });
				lazy.push_back(array{ 1, 0 });
				tree[i][1] = tree.size() - 1;
			}
			else {
				tree.push_back(tree[tree[i][1]]);
				lazy.push_back(lazy[tree[i][1]]);
				tree[i][1] = tree.size() - 1;
			}
			if (tree[i][2] == -1) {
				tree.push_back(array{ 0, -1, -1 });
				lazy.push_back(array{ 1, 0 });
				tree[i][2] = tree.size() - 1;
			}
			else {
				tree.push_back(tree[tree[i][2]]);
				lazy.push_back(lazy[tree[i][2]]);
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
	};
	auto update_1 = [&](int node, int l, int r, int a, int b) {
		tree.push_back(tree[node]);
		lazy.push_back(lazy[node]);
		node = tree.size() - 1;
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
		rec(rec, node, 0, n - 1);
		return node;
	};
	auto update_2 = [&](int node1, int node2, int l, int r) {
		tree.push_back(tree[node1]);
		lazy.push_back(lazy[node1]);
		node1 = tree.size() - 1;
		tree.push_back(tree[node2]);
		lazy.push_back(lazy[node2]);
		node2 = tree.size() - 1;
		auto rec = [&](const auto& self, int node1, int node2, int node_l, int node_r) -> void {
			push(node1, node_l, node_r);
			push(node2, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				tree[node1] = tree[node2];
				lazy[node1] = lazy[node2];
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, tree[node1][1], tree[node2][1], node_l, mid);
			self(self, tree[node1][2], tree[node2][2], mid + 1, node_r);
			tree[node1][0] = add(tree[tree[node1][1]][0], tree[tree[node1][2]][0]);
			tree[node2][0] = add(tree[tree[node2][1]][0], tree[tree[node2][2]][0]);
		};
		rec(rec, node1, node2, 0, n - 1);
		return node1;
	};
	auto query = [&](int node, int l, int r) {
		tree.push_back(tree[node]);
		lazy.push_back(lazy[node]);
		node = tree.size() - 1;
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> int {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return 0;
			if (l <= node_l && node_r <= r) return tree[node][0];
			int mid = (node_l + node_r) >> 1;
			int r1 = self(self, tree[node][1], node_l, mid);
			int r2 = self(self, tree[node][2], mid + 1, node_r);
			return add(r1, r2);
		};
		return rec(rec, node, 0, n - 1);
	};
	vector ret(0, 0);
	for (int i = 0; i < n; i++) {
		root[0] = update_1(root[0], i, i, 0, v[i]);
	}
	for (int iter = 0; iter < q; iter++) {
		auto [op, a, b, c, d, e] = qs[iter];
		if (op == 0) root[iter + 1] = update_1(root[a + 1], b, c - 1, d, e);
		if (op == 1) root[iter + 1] = update_2(root[a + 1], root[b + 1], c, d - 1);
		if (op == 2) ret.push_back(query(root[a + 1], b, c - 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0, 0, 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [op, a, b, c, d, e] : qs) {
		cin >> op >> a >> b >> c;
		if (op == 0) cin >> d >> e;
		if (op == 1) cin >> d;
	}
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}