#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](const auto& adj) {
	int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto dfs = [&](const auto& self, int cur) -> int {
		int ret = dfn[cur] = ++dfs_cnt;
		s.push_back(cur);
		for (int nxt : adj[cur]) {
			if (!dfn[nxt]) ret = min(ret, self(self, nxt));
			else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
		}
		if (ret == dfn[cur]) {
			scc_cnt++;
			while (s.size()) {
				int x = s.back(); s.pop_back();
				scc[x] = scc_cnt;
				if (x == cur) break;
			}
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
	return pair(scc_cnt, scc);
};

auto sol = [](int n, auto adj) {
	auto [scc_cnt, scc] = get_scc(adj);
	vector v(scc_cnt + 1, 0);
	vector g(scc_cnt + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		v[scc[i]]++;
		for (int j : adj[i]) {
			if (scc[i] == scc[j]) continue;
			g[scc[i]].push_back(scc[j]);
		}
	}
	for (int i = 1; i <= scc_cnt; i++) {
		sort(g[i].begin(), g[i].end());
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
	}
	vector dp(scc_cnt + 1, vector(scc_cnt + 1, -1));
	auto rec = [&](const auto& self, int a, int b) -> int {
		if (a < b) swap(a, b);
		int& ret = dp[a][b];
		if (ret != -1) return ret;
		ret = 0;
		for (int i : g[a]) {
			int val = self(self, i, b);
			if (i != b) val += v[i];
			ret = max(ret, val);
		}
		if (g[a].empty()) {
			for (int i : g[b]) {
				int val = self(self, a, i) + v[i];
				ret = max(ret, val);
			}
		}
		return ret;
	};
	int ret = 0;
	for (int i = 1; i <= scc_cnt; i++) {
		ret = max(ret, rec(rec, i, i) + v[i]);
		for (int j = i + 1; j <= scc_cnt; j++) {
			ret = max(ret, rec(rec, i, j) + v[i] + v[j]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x; cin >> x;
			if (x == 1) adj[i].push_back(j);
		}
	}
	cout << sol(n, adj) << '\n';
}