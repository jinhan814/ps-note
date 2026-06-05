#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v, auto e) {
	vector adj(n, vector(0, tuple(0, 0, 0)));
	for (int i = 0; i < m; i++) {
		auto [a, b, c] = e[i];
		adj[a].push_back(tuple(b, c, i));
		adj[b].push_back(tuple(a, c, i));
	}
	vector dp(1 << k, vector(n, i64(1) << 60));
	for (int i = 0; i < k; i++) {
		dp[1 << i][v[i]] = 0;
	}
	for (int mask = 1; mask < 1 << k; mask++) {
		for (int s = (mask - 1) & mask; s > 0; s = (s - 1) & mask) {
			int t = mask ^ s;
			for (int i = 0; i < n; i++) {
				dp[mask][i] = min(dp[mask][i], dp[s][i] + dp[t][i]);
			}
		}
		vector c(n, false);
		while (1) {
			int cur = -1;
			for (int p = 0; p < n; p++) {
				if (c[p]) continue;
				if (cur == -1 || dp[mask][cur] > dp[mask][p]) cur = p;
			}
			if (cur == -1) break;
			c[cur] = true;
			for (auto [nxt, cost, idx] : adj[cur]) {
				if (dp[mask][nxt] <= dp[mask][cur] + cost) continue;
				dp[mask][nxt] = dp[mask][cur] + cost;
			}
		}
	}
	i64 ret = dp[(1 << k) - 1][v[0]];
	vector buc(0, 0);
	auto rec = [&](const auto& self, int mask, int cur) -> void {
		for (int s = (mask - 1) & mask; s > 0; s = (s - 1) & mask) {
			int t = mask ^ s;
			if (dp[mask][cur] != dp[s][cur] + dp[t][cur]) continue;
			self(self, s, cur);
			self(self, t, cur);
			return;
		}
		for (auto [nxt, cost, idx] : adj[cur]) {
			if (dp[mask][cur] != dp[mask][nxt] + cost) continue;
			self(self, mask, nxt);
			buc.push_back(idx);
			return;
		}
	};
	rec(rec, (1 << k) - 1, v[0]);
	return pair(ret, buc);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0, 0 });
	for (auto& [a, b, c] : e) cin >> a >> b >> c;
	int k; cin >> k;
	vector v(k, 0);
	for (int i = 0; i < k; i++) cin >> v[i];
	auto [res, buc] = sol(n, m, k, v, e);
	cout << res << ' ' << buc.size() << '\n';
	for (int i : buc) cout << i << ' ';
	cout << '\n';
}