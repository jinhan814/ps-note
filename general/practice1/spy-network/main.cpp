#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

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

auto sol = [](int n, int m, i64 x, auto v, auto adj) {
	auto [scc_cnt, scc] = get_scc(adj);
	vector dp(scc_cnt + 1, i64(0));
	vector g(scc_cnt + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		dp[scc[i]] = gcd(dp[scc[i]], v[i]);
		for (int j : adj[i]) {
			if (scc[i] == scc[j]) continue;
			g[scc[i]].push_back(scc[j]);
		}
	}
	for (int i = scc_cnt; i >= 1; i--) {
		for (int j : g[i]) {
			dp[j] = gcd(dp[j], dp[i]);
		}
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		if (dp[scc[i]] != x) continue;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		i64 x; cin >> x;
		vector v(n + 1, i64(0));
		vector adj(n + 1, vector(0, 0));
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
		}
		for (int i = 1; i <= n; i++) cin >> v[i];
		cout << sol(n, m, x, v, adj) << '\n';
	}
}