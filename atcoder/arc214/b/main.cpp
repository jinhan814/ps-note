#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	if (n % 2 == 1) return -1;
	vector d(n + 1, -1);
	auto rec = [&](const auto& self, int cur) -> void {
		for (auto [nxt, cost] : adj[cur]) {
			if (d[nxt] != -1) continue;
			d[nxt] = d[cur] ^ cost;
			self(self, nxt);
		}
	};
	d[1] = 0;
	rec(rec, 1);
	int ret = 0;
	for (int i = 1; i <= n; i++) ret ^= d[i] ^ i;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector adj(n + 1, vector(0, pair(0, 0)));
		for (int i = 0; i < m; i++) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back(pair(b, c));
			adj[b].push_back(pair(a, c));
		}
		cout << sol(n, m, adj) << '\n';
	}
}