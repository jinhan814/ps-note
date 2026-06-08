#include <bits/stdc++.h>
using namespace std;

struct dinic {
	dinic(int n) : dep(n), idx(n), adj(n) {}
	void add_edge(int a, int b, int cap, int rcap = 0) {
		edge e{ b, (int)adj[b].size(), cap };
		edge r{ a, (int)adj[a].size(), rcap };
		adj[a].push_back(e);
		adj[b].push_back(r);
	}
	bool bfs(int s, int t) {
		fill(dep.begin(), dep.end(), 0);
		deque q{ s }; dep[s] = 1;
		while (q.size()) {
			int cur = q.front(); q.pop_front();
			for (const auto& [nxt, _, res] : adj[cur]) {
				if (res == 0 || dep[nxt]) continue;
				q.push_back(nxt);
				dep[nxt] = dep[cur] + 1;
			}
		}
		return dep[t] != 0;
	}
	int dfs(int cur, int t, int acc) {
		if (cur == t || acc == 0) return acc;
		for (int& i = idx[cur]; i < adj[cur].size(); i++) {
			auto& [nxt, inv, res] = adj[cur][i];
			if (res == 0 || dep[nxt] != dep[cur] + 1) continue;
			int val = dfs(nxt, t, min(acc, res));
			if (val == 0) continue;
			res -= val;
			adj[nxt][inv].res += val;
			return val;
		}
		return 0;
	}
	int flow(int s, int t) {
		int ret = 0;
		while (bfs(s, t)) {
			fill(idx.begin(), idx.end(), 0);
			while (1) {
				int f = dfs(s, t, 1 << 30);
				if (f == 0) break;
				ret += f;
			}
		}
		return ret;
	}
private:
	struct edge { int nxt, inv, res; };
	vector<int> dep, idx;
	vector<vector<edge>> adj;
};

auto sol = [](int n, int m, auto e) {
	dinic g(2 * n + 2);
	int s = 0, t = 2 * n + 1;
	for (int i = 1; i <= n; i++) {
		g.add_edge(s, i, 1);
		g.add_edge(n + i, t, 1);
	}
	for (auto [a, b] : e) {
		g.add_edge(a, n + b, 1);
		g.add_edge(b, n + a, 1);
	}
	return (2 * n - g.flow(s, t)) * 1013;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0 });
	for (auto& [a, b] : e) cin >> a >> b;
	cout << sol(n, m, e) << '\n';
}