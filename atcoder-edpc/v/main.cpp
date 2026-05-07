#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto adj) {
	auto mul = [&](int a, int b) -> int { return i64(a) * b % m; };
	vector dp(n + 1, 0);
	auto rec = [&](const auto& self, int cur) -> void {
		dp[cur] = 1;
		for (int nxt : adj[cur]) {
			auto it = find(adj[nxt].begin(), adj[nxt].end(), cur);
			adj[nxt].erase(it);
			self(self, nxt);
			dp[cur] = mul(dp[cur], dp[nxt] + 1);
		}
	};
	rec(rec, 1);
	vector ret(n + 1, 0);
	auto dfs = [&](const auto& self, int cur, int acc) -> void {
		ret[cur] = mul(dp[cur], acc);
		vector p(adj[cur].size(), 0);
		for (int i = 0; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			p[i] = dp[nxt] + 1;
			if (i > 0) p[i] = mul(p[i], p[i - 1]);
		}
		for (int i = adj[cur].size() - 1; i >= 0; i--) {
			int nxt = adj[cur][i];
			int nacc = acc;
			if (i > 0) nacc = mul(nacc, p[i - 1]);
			self(self, nxt, nacc + 1);
			acc = mul(acc, dp[nxt] + 1);
		}
	};
	dfs(dfs, 1, 1);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto res = sol(n, m, adj);
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}