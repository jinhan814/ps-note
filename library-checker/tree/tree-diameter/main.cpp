#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto adj) {
	vector d(n + 1, i64(0));
	vector p(n + 1, -1);
	auto rec = [&](const auto& self, int cur, int prv) -> int {
		int ret = cur;
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			d[nxt] = d[cur] + cost;
			p[nxt] = cur;
			int i = self(self, nxt, cur);
			if (d[ret] < d[i]) ret = i;
		}
		return ret;
	};
	int a = rec(rec, 1, -1);
	d[a] = 0;
	int b = rec(rec, a, -1);
	i64 x = d[b];
	vector c(0, 0);
	while (b != a) c.push_back(b), b = p[b];
	c.push_back(a);
	return pair(x, c);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	auto [opt, res] = sol(n, adj);
	cout << opt << ' ' << res.size() << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}