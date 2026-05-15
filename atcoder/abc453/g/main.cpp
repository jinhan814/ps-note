#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, i64 x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	i64 query(int l, int r) const {
		i64 ret = 0;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int m, int q, auto qs) {
	vector adj(1, vector(0, tuple(0, 0, 0)));
	vector buc(1, vector(0, tuple(0, 0, 0)));
	vector pos(n + 1, 0);
	int cnt = 0;
	for (auto [op, a, b, c] : qs) {
		if (op == 1) {
			pos[a] = pos[b];
		}
		else if (op == 2) {
			adj[pos[a]].push_back(tuple(adj.size(), b, c));
			adj.push_back(vector(0, tuple(0, 0, 0)));
			buc.push_back(vector(0, tuple(0, 0, 0)));
			pos[a] = adj.size() - 1;
		}
		else {
			buc[pos[a]].push_back(tuple(cnt, b, c));
			cnt++;
		}
	}
	vector ret(cnt, i64(0));
	segtree tree(m);
	auto rec = [&](const auto& self, int cur) -> void {
		for (auto [i, a, b] : buc[cur]) {
			ret[i] = tree.query(a, b);
		}
		for (auto [nxt, a, b] : adj[cur]) {
			i64 val = tree.query(a, a);
			tree.update(a, b);
			self(self, nxt);
			tree.update(a, val);
		}
	};
	rec(rec, 0);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector qs(q, array{ 0, 0, 0, 0 });
	for (auto& [op, a, b, c] : qs) {
		cin >> op >> a >> b;
		if (op != 1) cin >> c;
	}
	auto res = sol(n, m, q, qs);
	for (i64 x : res) cout << x << '\n';
}