#include <bits/stdc++.h>
using namespace std;

auto cent_decom = [](const auto& adj) {
	const int n = adj.size() - 1;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
		}
	};
	auto adjust = [&](int cur) {
		while (1) {
			int f = 0;
			for (auto [nxt, cost] : adj[cur]) {
				if (dep[nxt] || sz[cur] >= 2 * sz[nxt]) continue;
				sz[cur] -= sz[nxt], sz[nxt] += sz[cur];
				cur = nxt, f = 1;
				break;
			}
			if (!f) return cur;
		}
	};
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		cur = adjust(cur);
		par[cur] = prv;
		dep[cur] = dep[prv] + 1;
		for (auto [nxt, cost] : adj[cur]) {
			if (dep[nxt]) continue;
			self(self, nxt, cur);
		}
	};
	dfs(dfs, 1, 0);
	rec(rec, 1, 0);
	return pair(dep, par);
};

auto sol = [](int n, int k, auto adj) {
	auto [dep, par] = cent_decom(adj);
	vector dp(k + 1, 1 << 30);
	auto calc = [&](int cur) {
		auto f = [&](int x) { return dep[x] <= dep[cur]; };
		int ret = 1 << 30;
		dp[0] = 0;
		for (auto [nxt, cost] : adj[cur]) {
			if (f(nxt)) continue;
			auto calc = [&](const auto& self, int cur, int prv, int dep, int acc) -> void {
				if (acc > k) return;
				ret = min(ret, dp[k - acc] + dep);
				for (auto [nxt, cost] : adj[cur]) {
					if (f(nxt)) continue;
					if (nxt == prv) continue;
					self(self, nxt, cur, dep + 1, acc + cost);
				}
			};
			auto push = [&](const auto& self, int cur, int prv, int dep, int acc) -> void {
				if (acc > k) return;
				dp[acc] = min(dp[acc], dep);
				for (auto [nxt, cost] : adj[cur]) {
					if (f(nxt)) continue;
					if (nxt == prv) continue;
					self(self, nxt, cur, dep + 1, acc + cost);
				}
			};
			calc(calc, nxt, cur, 1, cost);
			push(push, nxt, cur, 1, cost);
		}
		for (auto [nxt, cost] : adj[cur]) {
			if (f(nxt)) continue;
			auto push = [&](const auto& self, int cur, int prv, int dep, int acc) -> void {
				if (acc > k) return;
				dp[acc] = 1 << 30;
				for (auto [nxt, cost] : adj[cur]) {
					if (f(nxt)) continue;
					if (nxt == prv) continue;
					self(self, nxt, cur, dep + 1, acc + cost);
				}
			};
			push(push, nxt, cur, 1, cost);
		}
		return ret;
	};
	int ret = 1 << 30;
	for (int i = 1; i <= n; i++) ret = min(ret, calc(i));
	if (ret >> 30) ret = -1;
	return ret;
};

int best_path(int n, int k, int e[][2], int w[]) {
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < n - 1; i++) {
		adj[e[i][0] + 1].push_back(pair(e[i][1] + 1, w[i]));
		adj[e[i][1] + 1].push_back(pair(e[i][0] + 1, w[i]));
	}
	return sol(n, k, adj);
}