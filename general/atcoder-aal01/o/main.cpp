#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, pair(i64(0), i64(0)));
	vector lazy(sz << 1, tuple(i64(0), i64(0), i64(1), i64(0)));
	auto push = [&](int i, int l, int r) {
		auto [a, b, c, d] = lazy[i];
		if (i < sz) {
			for (int j : { i << 1, i << 1 | 1 }) {
				auto& [v1, v2, v3, v4] = lazy[j];
				v1 = v1 + a * v3;
				v2 = v2 + a * v4 + b;
				v3 = c * v3;
				v4 = c * v4 + d;
			}
		}
		tree[i].first = tree[i].first + a * tree[i].second + b * (r - l + 1);
		tree[i].second = c * tree[i].second + d * (r - l + 1);
		lazy[i] = tuple(i64(0), i64(0), i64(1), i64(0));
	};
	auto update = [&](int l, int r, auto x) {
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
			tree[node].first = tree[node << 1].first + tree[node << 1 | 1].first;
			tree[node].second = tree[node << 1].second + tree[node << 1 | 1].second;
		};
		rec(rec, 1, 1, sz);
	};
	auto query = [&](int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return i64(0);
			if (l <= node_l && node_r <= r) return tree[node].first;
			int mid = (node_l + node_r) >> 1;
			i64 r1 = self(self, node << 1, node_l, mid);
			i64 r2 = self(self, node << 1 | 1, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 1, 1, sz);
	};
	vector buc(n + 1, vector(0, 0));
	for (int i = 0; i < q; i++) {
		buc[qs[i].second].push_back(i);
	}
	vector s(1, 0);
	vector ret(q, i64(0));
	for (int i = 1; i <= n; i++) {
		while (s.back() >= 1 && v[s.back()] >= v[i]) s.pop_back();
		update(s.back() + 1, i, tuple(i64(0), i64(0), i64(0), i64(v[i])));
		update(1, i, tuple(i64(1), i64(0), i64(1), i64(0)));
		s.push_back(i);
		for (int p : buc[i]) ret[p] = query(qs[p].first, i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, pair(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}