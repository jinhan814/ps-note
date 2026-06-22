#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, pair(i64(0), 0));
	vector lazy(sz << 1, pair(i64(0), pair(0, 0)));
	auto merge = [](auto a, auto b) {
		i64 v1 = max(a.first, b.first);
		int v2 = a.second + b.second;
		return pair(v1, v2);
	};
	auto push = [&](int i, int l, int r) {
		if (i < sz) {
			if (lazy[i].second.first) {
				lazy[i << 1].first = 0;
				lazy[i << 1].second.first = 1;
				lazy[i << 1 | 1].first = 0;
				lazy[i << 1 | 1].second.first = 1;
			}
			if (lazy[i].second.second) {
				lazy[i << 1].second.second ^= 1;
				lazy[i << 1 | 1].second.second ^= 1;
			}
			lazy[i << 1].first += lazy[i].first;
			lazy[i << 1 | 1].first += lazy[i].first;
		}
		if (lazy[i].second.first) tree[i].first = 0;
		if (lazy[i].second.second) tree[i].second = (r - l + 1) - tree[i].second;
		if (tree[i].second != r - l + 1) tree[i].first += lazy[i].first;
		lazy[i] = pair(i64(0), pair(0, 0));
	};
	auto update1 = [&](int l, int r, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (r < node_l || node_r < l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = pair(i64(x), pair(0, 0));
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) / 2;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 1, sz);
	};
	auto update2 = [&](int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (r < node_l || node_r < l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = pair(i64(0), pair(1, 1));
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) / 2;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 1, sz);
	};
	auto query = [&](int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (r < node_l || node_r < l) return pair(i64(0), 0);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) / 2;
			auto r1 = self(self, node << 1, node_l, mid);
			auto r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return merge(r1, r2);
		};
		return rec(rec, 1, 1, sz);
	};
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int l, r, x; cin >> l >> r >> x;
			update1(l, r, x);
		}
		else if (op == 2) {
			int l, r; cin >> l >> r;
			update2(l, r);
		}
		else {
			int l, r; cin >> l >> r;
			cout << query(l, r).first << '\n';
		}
	}
}