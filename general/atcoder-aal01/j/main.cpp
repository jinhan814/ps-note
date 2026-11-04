#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int q, auto qs) {
	vector c(0, i64(0));
	for (auto [op, a, b] : qs) {
		c.push_back(a);
		c.push_back(b + 1);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	int sz = 1 << (__lg(c.size() - 2 | 1) + 1);
	vector tree(sz << 1, pair(i64(0), i64(0)));
	vector lazy(sz << 1, false);
	auto merge = [](auto a, auto b) {
		return pair(a.first + b.first, a.second + b.second);
	};
	auto push = [&](int i) {
		if (!lazy[i]) return;
		if (i < sz) {
			lazy[i << 1] = !lazy[i << 1];
			lazy[i << 1 | 1] = !lazy[i << 1 | 1];
		}
		tree[i].first = tree[i].second - tree[i].first;
		lazy[i] = false;
	};
	auto update = [&](int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = !lazy[node];
				push(node);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, node << 1, node_l, mid);
			self(self, node << 1 | 1, mid + 1, node_r);
			tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
		};
		rec(rec, 1, 0, sz - 1);
	};
	auto query = [&](int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node);
			if (node_r < l || r < node_l) return i64(0);
			if (l <= node_l && node_r <= r) return tree[node].first;
			int mid = (node_l + node_r) >> 1;
			i64 r1 = self(self, node << 1, node_l, mid);
			i64 r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 0, sz - 1);
	};
	for (int i = 0; i + 1 < c.size(); i++) tree[i | sz].second = c[i + 1] - c[i];
	for (int i = sz - 1; i >= 1; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	vector ret(0, i64(0));
	for (auto [op, a, b] : qs) {
		a = lower_bound(c.begin(), c.end(), a) - c.begin();
		b = lower_bound(c.begin(), c.end(), b + 1) - c.begin() - 1;
		if (op == 1) update(a, b);
		else ret.push_back(query(a, b));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	vector qs(q, tuple(0, i64(0), i64(0)));
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(q, qs);
	for (i64 x : res) cout << x << '\n';
}