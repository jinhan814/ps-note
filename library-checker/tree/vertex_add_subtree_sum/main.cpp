#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	i64 query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto v, auto adj, auto qs) {
	fenwick tree(n);
	vector in(n, 0), out(n, 0);
	int ord = 0;
	auto rec = [&](const auto& self, int cur) -> void {
		in[cur] = ++ord;
		tree.update(in[cur], v[cur]);
		for (int nxt : adj[cur]) self(self, nxt);
		out[cur] = ord;
	};
	rec(rec, 0);
	vector ret(0, i64(0));
	for (auto [op, a, b] : qs) {
		if (op == 0) tree.update(in[a], b);
		else ret.push_back(tree.query(in[a], out[a]));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector adj(n, vector(0, 0));
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int p; cin >> p;
		adj[p].push_back(i);
	}
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op == 0) cin >> b;
	}
	auto res = sol(n, q, v, adj, qs);
	for (i64 x : res) cout << x << '\n';
}