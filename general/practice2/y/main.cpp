#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector dp(n + 1, 0);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			dp[cur] = max(dp[cur], dp[nxt] + 1);
		}
	};
	auto dfs = [&](const auto& self, int cur, int prv) -> int {
		int mx = -1, smx = -1, tmx = -1;
		for (int nxt : adj[cur]) {
			if (tmx < dp[nxt]) tmx = dp[nxt];
			if (smx < tmx) swap(smx, tmx);
			if (mx < smx) swap(mx, smx);
		}
		int ret = 0;
		if (tmx != -1) ret = mx + smx + tmx + 4;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			int v1 = dp[cur], v2 = dp[nxt];
			dp[cur] = (dp[nxt] != mx ? mx : smx) + 1;
			dp[nxt] = max(dp[nxt], dp[cur] + 1);
			ret = max(ret, self(self, nxt, cur));
			dp[cur] = v1;
			dp[nxt] = v2;
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