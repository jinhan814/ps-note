#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, int s, auto adj) {
	vector d(n + 1, i64(1) << 60);
	set pq{ pair(d[s] = 0, s) };
	while (pq.size()) {
		auto [cdist, cur] = *pq.begin(); pq.erase(pq.begin());
		for (auto [nxt, cost] : adj[cur]) {
			if (d[nxt] <= cdist + cost) continue;
			pq.erase(pair(d[nxt], nxt));
			pq.insert(pair(d[nxt] = cdist + cost, nxt));
		}
	}
	return d;
};

auto sol = [](int n, int m, int s, int t, int a, int b, auto adj) {
	auto ds = calc(n, s, adj);
	auto dt = calc(n, t, adj);
	auto da = calc(n, a, adj);
	auto db = calc(n, b, adj);
	vector g1(n + 1, vector(0, pair(0, 0)));
	vector g2(n + 1, vector(0, pair(0, 0)));
	vector c(n + 1, i64(1) << 60);
	for (int i = 1; i <= n; i++) {
		for (auto [j, cost] : adj[i]) {
			if (ds[i] + cost + dt[j] != ds[t]) continue;
			g1[i].push_back(pair(j, cost));
			g2[j].push_back(pair(i, cost));
			c[i] = min(c[i], db[i]);
			c[j] = min(c[j], db[j]);
		}
	}
	vector dp1(n + 1, i64(-1));
	vector dp2(n + 1, i64(-1));
	auto f = [&](const auto& self, int cur) -> i64 {
		i64& ret = dp1[cur];
		if (ret != -1) return ret;
		ret = c[cur];
		for (auto [nxt, cost] : g1[cur]) ret = min(ret, self(self, nxt));
		return ret;
	};
	auto g = [&](const auto& self, int cur) -> i64 {
		i64& ret = dp2[cur];
		if (ret != -1) return ret;
		ret = c[cur];
		for (auto [nxt, cost] : g2[cur]) ret = min(ret, self(self, nxt));
		return ret;
	};
	i64 ret = da[b];
	for (int i = 1; i <= n; i++) {
		ret = min(ret, da[i] + f(f, i));
		ret = min(ret, da[i] + g(g, i));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	int s, t, a, b; cin >> s >> t >> a >> b;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	cout << sol(n, m, s, t, a, b, adj) << '\n';
}