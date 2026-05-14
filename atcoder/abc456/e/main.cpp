#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v, auto adj) {
	for (int i = 1; i <= n; i++) {
		adj[i].push_back(i);
	}
	vector c(n + 1, vector(k, 0));
	auto rec = [&](const auto& self, int cur, int i) -> bool {
		c[cur][i] = 1;
		int ni = i + 1 < k ? i + 1 : 0;
		for (int nxt : adj[cur]) {
			if (v[nxt][ni] != 'o') continue;
			if (c[nxt][ni] == 1) return true;
			if (c[nxt][ni] == 0 && self(self, nxt, ni)) return true;
		}
		c[cur][i] = 2;
		return false;
	};
	for (int i = 1; i <= n; i++) {
		if (v[i][0] != 'o') continue;
		if (rec(rec, i, 0)) return true;
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector adj(n + 1, vector(0, 0));
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		int k; cin >> k;
		vector v(n + 1, string{});
		for (int i = 1; i <= n; i++) cin >> v[i];
		cout << (sol(n, m, k, v, adj) ? "Yes" : "No") << '\n';
	}
}