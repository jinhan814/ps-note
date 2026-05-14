#include"dreaming.h"
#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto adj) {
	int ret = 0;
	vector c(0, 0);
	vector d(n + 1, -1);
	for (int i = 1; i <= n; i++) {
		if (d[i] != -1) continue;
		auto rec = [&](const auto& self, int cur, int prv) -> int {
			int ret = cur;
			for (auto [nxt, cost] : adj[cur]) {
				if (nxt == prv) continue;
				d[nxt] = d[cur] + cost;
				int p = self(self, nxt, cur);
				if (d[ret] < d[p]) ret = p;
			}
			return ret;
		};
		auto dfs = [&](const auto& self, int cur, int prv, int acc) -> int {
			int ret = max(d[cur], acc);
			for (auto [nxt, cost] : adj[cur]) {
				if (nxt == prv) continue;
				ret = min(ret, self(self, nxt, cur, acc + cost));
			}
			return ret;
		};
		d[i] = 0;
		int a = rec(rec, i, -1);
		d[a] = 0;
		int b = rec(rec, a, -1);
		ret = max(ret, d[b]);
		c.push_back(dfs(dfs, b, -1, 0));
	}
	sort(c.begin(), c.end(), greater{});
	if (c.size() >= 2) ret = max(ret, c[0] + c[1] + k);
	if (c.size() >= 3) ret = max(ret, c[1] + c[2] + 2 * k);
	return ret;
};

int travelTime(int n, int m, int k, int a[], int b[], int c[]) {
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		adj[a[i] + 1].push_back(pair(b[i] + 1, c[i]));
		adj[b[i] + 1].push_back(pair(a[i] + 1, c[i]));
	}
	return sol(n, m, k, adj);
}