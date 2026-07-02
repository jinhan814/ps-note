#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr i64 inf = 4e18;

auto sol = [](int n, int op, auto v, auto adj) {
	vector sz(n + 1, 0);
	vector mx(n + 1, 0);
	vector acc(n + 1, i64(0));
	vector dp(n + 1, i64(0));
	auto rec = [&](const auto& self, int cur, int dep) -> void {
		sz[cur] = 1;
		mx[cur] = dep;
		acc[cur] = v[cur];
		for (int nxt : adj[cur]) {
			self(self, nxt, dep + 1);
			sz[cur] += sz[nxt];
			mx[cur] = max(mx[cur], mx[nxt]);
			acc[cur] += acc[nxt];
			dp[cur] += dp[nxt];
		}
		sort(adj[cur].begin(), adj[cur].end(), [&](int i, int j) {
			i64 v1 = sz[i] * acc[j];
			i64 v2 = sz[j] * acc[i];
			return v1 < v2;
		});
		int x = 1;
		for (int i : adj[cur]) {
			dp[cur] += x * acc[i];
			x += 2 * sz[i];
		}
	};
	rec(rec, 1, 0);
	if (op == 0) return pair(i64(2) * (n - 1), dp[1]);
	auto dfs = [&](const auto& self, int cur) -> i64 {
		if (adj[cur].empty()) return 0;
		vector p1(adj[cur].size(), 1);
		vector p2(adj[cur].size(), i64(0));
		for (int iter = 1; iter <= adj[cur].size() - 1; iter++) {
			int i = adj[cur][iter - 1];
			p1[iter] = p1[iter - 1] + 2 * sz[i];
		}
		for (int iter = adj[cur].size() - 1; iter >= 1; iter--) {
			int i = adj[cur][iter];
			p2[iter - 1] = p2[iter] + acc[i];
		}
		i64 ret = 0;
		i64 mn = inf;
		for (int iter = 0; iter < adj[cur].size(); iter++) {
			int i = adj[cur][iter];
			ret += dp[i] + p1[iter] * acc[i];
			if (mx[i] != mx[1]) continue;
			i64 val = p1.back() - 2 * sz[i] + 2 * sz[adj[cur].back()];
			i64 v1 = self(self, i) + val * acc[i];
			i64 v2 = dp[i] + p1[iter] * acc[i] + 2 * sz[i] * p2[iter];
			mn = min(mn, v1 - v2);
		}
		ret += mn;
		return ret;
	};
	return pair(i64(2) * (n - 1) - mx[1], dfs(dfs, 1));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, op; cin >> n >> op;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 2; i <= n; i++) {
		int p; cin >> p;
		cin >> v[i];
		adj[p].push_back(i);
	}
	auto [mn, opt] = sol(n, op, v, adj);
	cout << mn << ' ' << opt << '\n';
}