#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto adj) {
	vector sz(n + 1, 1);
	vector dp(n + 1, vector(k + 2, i64(-1)));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		dp[cur][0] = 0;
		int val = 0;
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) { val = cost; continue; }
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
			for (int i = min(sz[cur], k + 1); i >= 0; i--) {
				for (int j = 1; j <= min(sz[nxt], i); j++) {
					if (dp[cur][i - j] == -1) continue;
					if (dp[nxt][j] == -1) continue;
					dp[cur][i] = max(dp[cur][i], dp[cur][i - j] + dp[nxt][j]);
				}
			}
		}
		for (int x = min(sz[cur], k + 1); x >= 1; x--) {
			i64 v1 = dp[cur][x - 1];
			if (cur != 1) v1 = max(v1, dp[cur][x]);
			i64 v2 = 2 * min(x, k + 1 - x) * val;
			dp[cur][x] = v1 == -1 ? -1 : v1 + v2;
		}
	};
	rec(rec, 1, -1);
	return dp[1][k + 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n, k; cin >> n >> k;
		vector adj(n + 1, vector(0, pair(0, 0)));
		for (int i = 2; i <= n; i++) {
			int p, x; cin >> p >> x;
			adj[i].push_back(pair(p, x));
			adj[p].push_back(pair(i, x));
		}
		cout << "Case " << iter << ": ";
		cout << sol(n, k, adj) << '\n';
	}
}