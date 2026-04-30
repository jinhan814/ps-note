#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector ret(n + 1, false);
	vector dp(n + 1, 0);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			if (dp[nxt] == 0) dp[cur]++;
		}
	};
	auto reroot = [&](const auto& self, int cur, int prv) -> void {
		ret[cur] = dp[cur] > 0;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			if (dp[nxt] == 0) dp[cur]--;
			if (dp[cur] == 0) dp[nxt]++;
			self(self, nxt, cur);
			if (dp[cur] == 0) dp[nxt]--;
			if (dp[nxt] == 0) dp[cur]++;
		}
	};
	rec(rec, 1, 0);
	reroot(reroot, 1, 0);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto res = sol(n, adj);
	for (int i = 1; i <= n; i++) {
		cout << (res[i] ? "Zeze" : "Portuga") << '\n';
	}
}