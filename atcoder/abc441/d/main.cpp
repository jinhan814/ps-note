#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, int l, int r, auto adj) {
	vector c(n + 1, false);
	auto rec = [&](const auto& self, int dep, int cur, int acc) -> void {
		if (acc > r) return;
		if (dep == k && acc >= l) c[cur] = true;
		if (dep == k) return;
		for (auto [nxt, cost] : adj[cur]) self(self, dep + 1, nxt, acc + cost);
	};
	rec(rec, 0, 1, 0);
	vector ret(0, 0);
	for (int i = 1; i <= n; i++) {
		if (!c[i]) continue;
		ret.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k, l, r; cin >> n >> m >> k >> l >> r;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
	}
	auto res = sol(n, m, k, l, r, adj);
	for (int x : res) cout << x << ' ';
	cout << '\n';
}