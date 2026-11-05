#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() : acc(0), mx(-(i64(1) << 60)) {}
	node(int x) : acc(x), mx(x) {}
	node operator+ (const node& x) const {
		node ret;
		ret.acc = acc + x.acc;
		ret.mx = max(mx, acc + x.mx);
		return ret;
	}
	i64 get_acc() const {
		return acc;
	}
	i64 get_mx() const {
		return mx;
	}
private:
	i64 acc, mx;
};

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, array{ node(), node(), node() });
	vector lazy(sz << 1, array{ 0, 1, 2 });
	for (int i = 1; i <= n; i++) {
		int p = sz | i - 1;
		tree[p][0] = node(v[i][0]);
		tree[p][1] = node(v[i][1]);
		tree[p][2] = node(v[i][2]);
	}
	for (int i = sz - 1; i >= 1; i--) {
		tree[i][0] = tree[i << 1][0] + tree[i << 1 | 1][0];
		tree[i][1] = tree[i << 1][1] + tree[i << 1 | 1][1];
		tree[i][2] = tree[i << 1][2] + tree[i << 1 | 1][2];
	}
	auto apply = [](auto& v, auto p) {
		auto c = v;
		for (int i = 0; i < p.size(); i++) v[i] = c[p[i]];
	};
	auto push = [&](int i) {
		if (i < sz) {
			apply(lazy[i << 1], lazy[i]);
			apply(lazy[i << 1 | 1], lazy[i]);
		}
		apply(tree[i], lazy[i]);
		lazy[i] = array{ 0, 1, 2 };
	};
	auto update = [&](int l, int r, auto p) {
		auto rec = [&](const auto& self, int i, int node_l, int node_r) {
			push(i);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[i] = p;
				push(i);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, i << 1, node_l, mid);
			self(self, i << 1 | 1, mid + 1, node_r);
			tree[i][0] = tree[i << 1][0] + tree[i << 1 | 1][0];
			tree[i][1] = tree[i << 1][1] + tree[i << 1 | 1][1];
			tree[i][2] = tree[i << 1][2] + tree[i << 1 | 1][2];
		};
		rec(rec, 1, 1, sz);
	};
	auto query = [&](int p) {
		i64 acc = 0;
		auto rec = [&](const auto& self, int i, int node_l, int node_r) {
			push(i);
			if (node_r < p) return n + 1;
			if (node_l >= p && acc + tree[i][0].get_mx() <= 0) {
				acc += tree[i][0].get_acc();
				return n + 1;
			}
			if (node_l == node_r) {
				acc += tree[i][0].get_acc();
				return acc > 0 ? node_l : n + 1;
			}
			int mid = (node_l + node_r) >> 1;
			int res = self(self, i << 1, node_l, mid);
			if (res <= mid) return res;
			return self(self, i << 1 | 1, mid + 1, node_r);
		};
		return rec(rec, 1, 1, sz);
	};
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) update(a, b, array{ 1, 0, 2 });
		else if (op == 2) update(a, b, array{ 0, 2, 1 });
		else if (op == 3) update(a, b, array{ 2, 1, 0 });
		else ret.push_back(query(a));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, array{ 0, 0, 0 });
	vector qs(q, tuple(0, 0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i][0];
	for (int i = 1; i <= n; i++) cin >> v[i][1];
	for (int i = 1; i <= n; i++) cin >> v[i][2];
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op != 4) cin >> b;
	}
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}