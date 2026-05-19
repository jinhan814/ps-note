#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto adj, auto qs) {
	vector dep(n, 0);
	vector sp(19, vector(n, 0));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			sp[0][nxt] = cur;
			self(self, nxt, cur);
		}
	};
	rec(rec, 0, -1);
	for (int bit = 1; bit <= 18; bit++) {
		for (int i = 0; i < n; i++) {
			sp[bit][i] = sp[bit - 1][sp[bit - 1][i]];
		}
	}
	auto lca = [&](int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		for (int bit = 18; bit >= 0; bit--) {
			if (~(dep[a] - dep[b]) >> bit & 1) continue;
			a = sp[bit][a];
		}
		if (a == b) return a;
		for (int bit = 18; bit >= 0; bit--) {
			if (sp[bit][a] == sp[bit][b]) continue;
			a = sp[bit][a];
			b = sp[bit][b];
		}
		return sp[0][a];
	};
	auto calc = [&](int a, int b, int k) {
		int c = lca(a, b);
		int d = dep[a] + dep[b] - 2 * dep[c];
		if (k > d) return -1;
		if (k > dep[a] - dep[c]) k = d - k, swap(a, b);
		for (int bit = 18; bit >= 0; bit--) {
			if (~k >> bit & 1) continue;
			a = sp[bit][a];
		}
		return a;
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b, c] = qs[i];
		ret[i] = calc(a, b, c);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector adj(n + 1, vector(0, 0));
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (auto& [a, b, c] : qs) cin >> a >> b >> c;
	auto res = sol(n, q, adj, qs);
	for (int x : res) cout << x << '\n';
}