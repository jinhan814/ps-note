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

auto get_hld = [](auto adj) {
	int n = adj.size();
	vector sz(n, 1), dep(n, 0), par(n, 0);
	vector in(n, 0), out(n, 0), top(n, 0);
	int ord = 0;
	auto dfs1 = [&](const auto& self, int cur) -> void {
		for (int& nxt : adj[cur]) {
			adj[nxt].erase(find(adj[nxt].begin(), adj[nxt].end(), cur));
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			self(self, nxt);
			sz[cur] += sz[nxt];
			if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
		}
	};
	auto dfs2 = [&](const auto& self, int cur) -> void {
		in[cur] = ++ord;
		for (int nxt : adj[cur]) {
			top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
			self(self, nxt);
		}
		out[cur] = ord;
	};
	dfs1(dfs1, 0);
	dfs2(dfs2, 0);
	return tuple(dep, par, in, top);
};

auto sol = [](int n, int q, auto v, auto adj, auto qs) {
	auto [dep, par, in, top] = get_hld(adj);
	fenwick tree(n);
	for (int i = 0; i < n; i++) tree.update(in[i], v[i]);
	auto calc = [&](int a, int b) {
		i64 ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			ret += tree.query(in[top[a]], in[a]);
			a = par[top[a]];
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret += tree.query(in[a], in[b]);
		return ret;
	};
	vector ret(0, i64(0));
	for (auto [op, a, b] : qs) {
		if (op == 0) tree.update(in[a], b);
		else ret.push_back(calc(a, b));
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
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, adj, qs);
	for (i64 x : res) cout << x << '\n';
}