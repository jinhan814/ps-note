#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int q, auto adj, auto qs) {
	vector par(n + 1, 0);
	vector dep(n + 1, 0);
	vector acc(n + 1, i64(0));
	vector e(0, i64(0));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			if (nxt != 1 && par[nxt] == 0) {
				par[nxt] = cur;
				dep[nxt] = dep[cur] + 1;
				acc[nxt] = acc[cur] ^ cost;
				self(self, nxt, cur);
			}
			else {
				e.push_back(acc[nxt] ^ acc[cur] ^ cost);
			}
		}
	};
	rec(rec, 1, 0);
	for (int bit = 59, piv = 0; bit >= 0; bit--) {
		if (piv == e.size()) break;
		if (~e[piv] >> bit & 1) {
			for (int i = piv + 1; i < e.size(); i++) {
				if (~e[i] >> bit & 1) continue;
				swap(e[piv], e[i]);
				break;
			}
			if (~e[piv] >> bit & 1) continue;
		}
		for (int i = 0; i < e.size(); i++) {
			if (i == piv) continue;
			if (~e[i] >> bit & 1) continue;
			e[i] ^= e[piv];
		}
		piv++;
	}
	while (e.size() && e.back() == 0) e.pop_back();
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		i64 val = acc[a] ^ acc[b];
		for (i64 x : e) {
			if (val <= (val ^ x)) continue;
			val ^= x;
		}
		ret[i] = val;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector adj(n + 1, vector(0, pair(0, i64(0))));
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		i64 c; cin >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, m, q, adj, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}