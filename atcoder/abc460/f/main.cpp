#include <bits/stdc++.h>
using namespace std;

auto get_hld = [](auto adj) {
	int n = adj.size() - 1;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
	vector in(n + 1, 0), out(n + 1, 0), top(n + 1, 0);
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
	dfs1(dfs1, 1);
	dfs2(dfs2, top[1] = 1);
	return tuple(dep, par, in, top);
};

auto sol = [](int n, int q, auto adj, auto qs) {
	auto [dep, par, in, top] = get_hld(adj);
	auto lca = [&](int a, int b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			a = par[top[a]];
		}
		if (dep[a] > dep[b]) swap(a, b);
		return a;
	};
	auto dist = [&](int a, int b) {
		int u = lca(a, b);
		return dep[a] + dep[b] - 2 * dep[u];
	};
	auto merge = [&](auto a, auto b) {
		vector buc(0, 0);
		if (a.first != -1) buc.push_back(a.first);
		if (a.second != -1) buc.push_back(a.second);
		if (b.first != -1) buc.push_back(b.first);
		if (b.second != -1) buc.push_back(b.second);
		if (buc.empty()) return pair(-1, -1);
		if (buc.size() == 1) return pair(buc[0], -1);
		pair ret(-1, -1);
		int mx = -1;
		for (int i = 0; i < buc.size(); i++) {
			for (int j = i + 1; j < buc.size(); j++) {
				int val = dist(buc[i], buc[j]);
				if (mx >= val) continue;
				ret = pair(buc[i], buc[j]);
				mx = val;
			}
		}
		return ret;
	};
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, pair(-1, -1));
	vector c(n + 1, false);
	for (int i = 1; i <= n; i++) {
		tree[i - 1 | sz] = pair(i, -1);
		c[i] = true;
	}
	for (int i = sz - 1; i >= 1; i--) {
		tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		int x = qs[i];
		pair val(c[x] ? -1 : x, -1);
		c[x] = !c[x];
		tree[--x |= sz] = val;
		while (x >>= 1) tree[x] = merge(tree[x << 1], tree[x << 1 | 1]);
		ret[i] = dist(tree[1].first, tree[1].second);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int q; cin >> q;
	vector qs(q, 0);
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, adj, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}