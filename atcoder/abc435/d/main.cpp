#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int q, auto adj, auto qs) {
	vector c(n + 1, false);
	auto rec = [&](const auto& self, int cur) {
		if (c[cur]) return;
		c[cur] = true;
		for (int nxt : adj[cur]) self(self, nxt);
	};
	vector ret(0, false);
	for (auto [op, i] : qs) {
		if (op == 1) rec(rec, i);
		else ret.push_back(c[i]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[b].push_back(a);
	}
	int q; cin >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [op, i] : qs) cin >> op >> i;
	auto res = sol(n, m, q, adj, qs);
	for (bool x : res) cout << (x ? "Yes" : "No") << '\n';
}