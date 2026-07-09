#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int a, int b, auto adj) {
	i64 ret = i64(1) << 60;
	{
		vector d(n + 1, -1); d[1] = 0;
		deque q(1, 1);
		while (q.size()) {
			int cur = q.front(); q.pop_front();
			for (int nxt : adj[cur]) {
				if (d[nxt] != -1) continue;
				d[nxt] = d[cur] + 1;
				q.push_back(nxt);
			}
		}
		if (d[n] != -1) ret = min(ret, i64(d[n]) * a);
	}
	{
		vector d(n + 1, -1); d[1] = 0;
		deque q(1, 1);
		vector s(0, 0);
		vector c(n + 1, false);
		for (int i = 2; i <= n; i++) s.push_back(i);
		while (q.size()) {
			int cur = q.front(); q.pop_front();
			vector ns(0, 0);
			for (int nxt : adj[cur]) c[nxt] = true;
			for (int nxt : s) {
				if (c[nxt]) ns.push_back(nxt);
				else d[nxt] = d[cur] + 1, q.push_back(nxt);
			}
			for (int nxt : adj[cur]) c[nxt] = false;
			s.swap(ns);
		}
		if (d[n] != -1) ret = min(ret, i64(d[n]) * b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b; cin >> n >> m >> a >> b;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, m, a, b, adj) << '\n';
}