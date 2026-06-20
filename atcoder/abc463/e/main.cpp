#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v, auto adj) {
	vector d(n + 1, i64(1) << 60);
	set pq{ pair(d[1] = 0, 1) };
	while (pq.size()) {
		auto [cdist, cur] = *pq.begin();
		pq.erase(pq.begin());
		if (cur != 0) {
			for (auto [nxt, cost] : adj[cur]) {
				if (d[nxt] <= cdist + cost) continue;
				pq.erase(pair(d[nxt], nxt));
				pq.insert(pair(d[nxt] = cdist + cost, nxt));
			}
			if (d[0] <= cdist + v[cur] + k) continue;
			pq.erase(pair(d[0], 0));
			pq.insert(pair(d[0] = cdist + v[cur] + k, 0));
		}
		else {
			for (int i = 1; i <= n; i++) {
				if (d[i] <= cdist + v[i]) continue;
				pq.erase(pair(d[i], i));
				pq.insert(pair(d[i] = cdist + v[i], i));
			}
		}
	}
	return d;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, m, k, v, adj);
	for (int i = 2; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}