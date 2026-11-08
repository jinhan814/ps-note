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

auto sol = [](int n, int q, auto qs) {
	vector buc(n + 2, vector(0, tuple(0, 0, 0)));
	for (auto [a, b, c, d] : qs) {
		buc[a].push_back(tuple(b, d, 1));
		buc[c + 1].push_back(tuple(b, d, -1));
	};
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, pair(0, 0));
	vector lazy(sz << 1, 0);
	auto merge = [](auto a, auto b) {
		if (a.second > b.second) swap(a, b);
		if (a.second == b.second) a.first = add(a.first, b.first);
		return a;
	};
	auto push = [&](int i) {
		if (i < sz) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		tree[i].second += lazy[i];
		lazy[i] = 0;
	};
	auto update = [&](int l, int r, int x) {
		auto rec = [&](const auto& self, int i, int node_l, int node_r) {
			push(i);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[i] = x;
				push(i);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, i << 1, node_l, mid);
			self(self, i << 1 | 1, mid + 1, node_r);
			tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
		};
		rec(rec, 1, 1, sz);
	};
	auto query = [&](int l, int r) {
		auto rec = [&](const auto& self, int i, int node_l, int node_r) {
			push(i);
			if (node_r < l || r < node_l) return pair(0, 1 << 30);
			if (l <= node_l && node_r <= r) return tree[i];
			int mid = (node_l + node_r) >> 1;
			auto r1 = self(self, i << 1, node_l, mid);
			auto r2 = self(self, i << 1 | 1, mid + 1, node_r);
			return merge(r1, r2);
		};
		return rec(rec, 1, 1, sz);
	};
	for (int i = 1; i <= n; i++) tree[i - 1 | sz].first = i;
	for (int i = sz - 1; i >= 1; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		for (auto [l, r, x] : buc[i]) update(l, r, x);
		auto [a, b] = query(1, n);
		if (b == 0) ret = add(ret, mul(i, a));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, tuple(0, 0, 0, 0));
	for (auto& [a, b, c, d] : qs) cin >> a >> b >> c >> d;
	cout << sol(n, q, qs) << '\n';
}