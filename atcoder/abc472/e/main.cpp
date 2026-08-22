#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	vector par(n + 1, -1);
	vector c(n + 1, -1);
	int a = -1, b = -1;
	auto rec = [&](const auto& self, int cur, int col) -> bool {
		c[cur] = col;
		for (int nxt : adj[cur]) {
			if (c[nxt] != -1) {
				if (c[cur] != c[nxt]) continue;
				a = cur;
				b = nxt;
				return true;
			}
			else {
				par[nxt] = cur;
				if (self(self, nxt, col ^ 1)) return true;
			}
		}
		return false;
	};
	if (!rec(rec, 1, 0) == -1) return vector(0, 0);
	vector ret(0, 0);
	while (a != b) ret.push_back(a), a = par[a];
	ret.push_back(a);
	return ret;
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
		auto res = sol(n, m, adj);
		if (res.size()) {
			cout << res.size() << '\n';
			for (int x : res) cout << x << ' ';
			cout << '\n';
		}
		else {
			cout << -1 << '\n';
		}
	}
}