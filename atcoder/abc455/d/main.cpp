#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector par(n + 1, -1);
	while (q--) {
		int a, b; cin >> a >> b;
		par[a] = b;
	}
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		if (par[i] == -1) continue;
		adj[par[i]].push_back(i);
	}
	vector res(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (par[i] != -1) continue;
		auto rec = [&](const auto& self, int cur) -> void {
			res[i]++;
			for (int nxt : adj[cur]) self(self, nxt);
		};
		rec(rec, i);
	}
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}