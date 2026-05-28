#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector dp(n + 1, 0);
	auto rec = [&](const auto& self, int cur) -> void {
		if (adj[cur].size() >= 2) dp[cur] = 1;
		for (int nxt : adj[cur]) {
			auto it = find(adj[nxt].begin(), adj[nxt].end(), cur);
			adj[nxt].erase(it);
			self(self, nxt);
			if (adj[cur].size() >= 3) dp[cur] = max(dp[cur], dp[nxt] + 1);
		}
	};
	rec(rec, 1);
	int ret = 1;
	for (int i = 1; i <= n; i++) {
		int cnt = adj[i].size() + (i != 1);
		int mx = -1;
		ret = max(ret, dp[i]);
		for (int j : adj[i]) {
			if (cnt >= 3) ret = max(ret, dp[j] + 1);
			if (cnt >= 4) ret = max(ret, dp[j] + mx + 1);
			mx = max(mx, dp[j]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		cout << sol(n, adj) << '\n';
	}
}