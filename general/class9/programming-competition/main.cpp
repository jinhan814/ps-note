#include <bits/stdc++.h>
using namespace std;

struct mcmf {
	mcmf(int n) : in(n), dist(n), prv(n), adj(n) {}
	void add_edge(int a, int b, int cap, int cost) {
		edge e{ b, (int)adj[b].size(), cap, cost };
		edge r{ a, (int)adj[a].size(), 0, -cost };
		adj[a].push_back(e);
		adj[b].push_back(r);
	}
	bool augment(int s, int t) {
		fill(in.begin(), in.end(), 0);
		fill(dist.begin(), dist.end(), 1 << 30);
		deque q{ s }; in[s] = 1; dist[s] = 0;
		while (q.size()) {
			int cur = q.front(); q.pop_front(); in[cur] = 0;
			for (auto [nxt, inv, res, cost] : adj[cur]) {
				if (res == 0 || dist[nxt] <= dist[cur] + cost) continue;
				dist[nxt] = dist[cur] + cost;
				prv[nxt] = inv;
				if (in[nxt] == 0) in[nxt] = 1, q.push_back(nxt);
			}
		}
		return dist[t] < 1 << 30;
	}
	pair<int, int> flow(int s, int t) {
		int res = 0, acc = 0;
		while (augment(s, t)) {
			int f = 1 << 30;
			for (int i = t; i != s; i = adj[i][prv[i]].nxt) {
				auto [nxt, inv, res, cost] = adj[i][prv[i]];
				f = min(f, adj[nxt][inv].res);
			}
			res += f;
			acc += f * dist[t];
			for (int i = t; i != s; i = adj[i][prv[i]].nxt) {
				auto& [nxt, inv, res, cost] = adj[i][prv[i]];
				res += f;
				adj[nxt][inv].res -= f;
			}
		}
		return pair(res, acc);
	}
private:
	struct edge { int nxt, inv, res, cost; };
	vector<int> in, dist, prv;
	vector<vector<edge>> adj;
};

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), greater{});
	mcmf g(2 * n + 2);
	int s = 2 * n, t = 2 * n + 1;
	for (int i = 0; i < n; i++) {
		g.add_edge(s, i, 1, 0);
		g.add_edge(n + i, t, v[i][2] - (i > 0), 0);
		for (int j = 0; j < i; j++) {
			int v1 = v[i][0] ^ v[j][0];
			int v2 = v[i][1] + v[j][1];
			g.add_edge(i, n + j, 1, -(v1 - v2));
		}
	}
	return -g.flow(s, t).second;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0];
	for (int i = 0; i < n; i++) cin >> v[i][1];
	for (int i = 0; i < n; i++) cin >> v[i][2];
	cout << sol(n, v) << '\n';
}