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
	tuple<int, vector<int>, vector<int>> min_cut(int s, int t) {
		int ret = flow(s, t);
		vector a(0, 0), b(0, 0);
		for (int i = 0; i < dep.size(); i++) {
			if (dep[i] != 0) a.push_back(i);
			else b.push_back(i);
		}
		return tuple(ret, a, b);
	}
private:
	struct edge { int nxt, inv, res; };
	vector<int> dep, idx;
	vector<vector<edge>> adj;
};

auto sol = [](int n, int a, int b, auto v) {
	vector g(n, vector(n, vector(0, pair(0, 0))));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == '#') continue;
			for (int d = 0; d < 4; d++) {
				int nx = i + ("0022"[d] - '1') * a;
				int ny = j + ("0202"[d] - '1') * b;
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (v[nx][ny] == '#') continue;
				g[i][j].push_back(pair(nx, ny));
			}
			for (int d = 0; d < 4; d++) {
				int nx = i + ("0022"[d] - '1') * b;
				int ny = j + ("0202"[d] - '1') * a;
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (v[nx][ny] == '#') continue;
				g[i][j].push_back(pair(nx, ny));
			}
		}
	}
	vector c(n, vector(n, -1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == '#') continue;
			if (c[i][j] != -1) continue;
			auto rec = [&](const auto& self, int x, int y, int val) -> void {
				c[x][y] = val;
				for (auto [nx, ny] : g[x][y]) {
					if (c[nx][ny] != -1) continue;
					self(self, nx, ny, val ^ 1);
				}
			};
			rec(rec, i, j, 0);
		}
	}
	dinic flow(n * n + 2);
	int s = n * n, t = n * n + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == '#') continue;
			if (c[i][j] == 0) {
				flow.add_edge(s, i * n + j, 1);
				for (auto [nx, ny] : g[i][j]) {
					flow.add_edge(i * n + j, nx * n + ny, 1 << 30);
				}
			}
			else {
				flow.add_edge(i * n + j, t, 1);
			}
		}
	}
	auto [cnt, v1, v2] = flow.min_cut(s, t);
	vector p(n * n + 2, 0);
	for (int i : v1) p[i] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == '#') continue;
			if (c[i][j] == p[i * n + j]) continue;
			v[i][j] = 'o';
		}
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, a, b, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}