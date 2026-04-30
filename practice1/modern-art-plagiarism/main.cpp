#include <bits/stdc++.h>
using namespace std;

auto bipartite_matching = [](const auto& adj) {
	const int n = adj.size() - 1;
	vector par(n + 1, 0), c(n + 1, 0);
	auto dfs = [&](const auto& self, int cur) -> bool {
		if (c[cur]++) return 0;
		for (int nxt : adj[cur])
			if (!par[nxt] || self(self, par[nxt]))
				return par[nxt] = cur, 1;
		return 0;
	};
	int res = 0;
	for (int i = 1; i <= n; i++) {
		fill(c.begin(), c.end(), 0);
		if (dfs(dfs, i)) res++;
	}
	return res;
};

auto sol = [](int n1, int n2, auto g1, auto g2) {
	map cache{ pair(array{ 0, 0, 0, 0 }, 0) };
	auto rec = [&](const auto& self, int c1, int p1, int c2, int p2) -> bool {
		if (cache.count({ c1, p1, c2, p2 })) return cache[{ c1, p1, c2, p2 }];
		vector buc1(0, 0), buc2(0, 0);
		for (int x : g1[c1]) if (x != p1) buc1.push_back(x);
		for (int x : g2[c2]) if (x != p2) buc2.push_back(x);
		if (buc1.size() < buc2.size()) return 0;
		vector adj(buc1.size() + buc2.size() + 1, vector(0, 0));
		for (int i = 0; i < buc1.size(); i++) for (int j = 0; j < buc2.size(); j++) {
			if (!self(self, buc1[i], c1, buc2[j], c2)) continue;
			adj[i + 1].push_back(buc1.size() + j + 1);
		}
		if (bipartite_matching(adj) == buc2.size()) return cache[{ c1, p1, c2, p2 }] = true;
		return cache[{ c1, p1, c2, p2 }] = false;
	};
	for (int i = 1; i <= n1; i++) {
		if (!rec(rec, i, -1, 1, -1)) continue;
		return true;
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n1; cin >> n1;
		vector g1(n1 + 1, vector(0, 0));
		for (int i = 1; i < n1; i++) {
			int a, b; cin >> a >> b;
			g1[a].push_back(b);
			g1[b].push_back(a);
		}
		int n2; cin >> n2;
		vector g2(n2 + 1, vector(0, 0));
		for (int i = 1; i < n2; i++) {
			int a, b; cin >> a >> b;
			g2[a].push_back(b);
			g2[b].push_back(a);
		}
		cout << "Case #" << iter << ": ";
		cout << (sol(n1, n2, g1, g2) ? "YES" : "NO") << '\n';
	}
}