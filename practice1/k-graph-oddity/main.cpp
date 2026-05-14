#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	int k = 1;
	for (int i = 1; i <= n; i++) {
		int val = adj[i].size() | 1;
		if (k < val) k = val;
	}
	int p = 1;
	while (adj[p].size() == k) p++;
	vector ret(n + 1, 1);
	vector dfn(n + 1, -1);
	int ord = 0;
	auto rec = [&](const auto& self, int cur) -> void {
		dfn[cur] = ++ord;
		vector c(k + 1, false);
		for (int nxt : adj[cur]) {
			if (dfn[nxt] == -1) self(self, nxt);
			if (dfn[nxt] > dfn[cur]) c[ret[nxt]] = true;
		}
		while (c[ret[cur]]) ret[cur]++;
	};
	rec(rec, p);
	return pair(k, ret);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto [k, res] = sol(n, m, adj);
	cout << k << '\n';
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}