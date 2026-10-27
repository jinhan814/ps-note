#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int a, int b, auto adj) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < adj[i].size(); j++) {
			if (adj[i][0] < adj[i][j]) continue;
			swap(adj[i][0], adj[i][j]);
		}
	}
	vector d(n + 1, 1 << 30); d[a] = 0;
	deque q(1, a);
	while (q.size()) {
		int cur = q.front(); q.pop_front();
		for (int i = 0; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (i == 0 && d[nxt] > d[cur]) {
				d[nxt] = d[cur];
				q.push_front(nxt);
			}
			if (i != 0 && d[nxt] > d[cur] + 1) {
				d[nxt] = d[cur] + 1;
				q.push_back(nxt);
			}
		}
	}
	if (d[b] == 1 << 30) return -1;
	return d[b];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b; cin >> n >> m >> a >> b;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	cout << sol(n, m, a, b, adj) << '\n';
}