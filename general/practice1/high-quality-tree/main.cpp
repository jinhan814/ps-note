#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector dep(n + 1, 0);
	vector dp(n + 1, 0);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		vector c(0, 0);
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			self(self, nxt, cur);
			c.push_back(dp[nxt]);
		}
		if (c.empty()) dp[cur] = dep[cur];
		else if (c.size() == 1) dp[cur] = dep[cur] + 1;
		else if (c[0] == c[1]) dp[cur] = c[0];
		else dp[cur] = min(c[0], c[1]) + 1;
	};
	auto dfs = [&](const auto& self, int cur, int prv) -> int {
		int ret = 0;
		if (dep[cur] > dp[cur]) ret++;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dp[nxt] = min(dp[nxt], dp[cur]);
			ret += self(self, nxt, cur);
		}
		return ret;
	};
	rec(rec, 1, -1);
	return dfs(dfs, 1, -1);
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
	cout << sol(n, adj) << '\n';
}