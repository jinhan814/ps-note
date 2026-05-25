#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, int k, auto v) {
	vector tree(1, array{ -1, -1, 0 });
	auto update = [&](int x) {
		int p = 0;
		for (int bit = 29; bit >= 0; bit--) {
			if (tree[p][x >> bit & 1] == -1) {
				tree.push_back(array{ -1, -1, 0 });
				tree[p][x >> bit & 1] = tree.size() - 1;
			}
			tree[p][2]++;
			p = tree[p][x >> bit & 1];
		}
		tree[p][2]++;
	};
	auto query = [&](int x) {
		int ret = 0;
		int p = 0;
		for (int bit = 29; bit >= 0; bit--) {
			if (k >> bit & 1) {
				int i = tree[p][x >> bit & 1];
				if (i != -1) ret += tree[i][2];
			}
			p = tree[p][(x ^ k) >> bit & 1];
			if (p == -1) break;
		}
		if (p != -1) ret += tree[p][2];
		return ret;
	};
	i64 ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += query(v[i]);
		update(v[i]);
	}
	return ret;
};

auto sol = [](int n, int m, int k, auto adj) {
	vector par(n + 1, 0);
	vector dep(n + 1, 0);
	vector acc(n + 1, 0);
	vector e(0, 0);
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
	for (int bit = 29, piv = 0; bit >= 0; bit--) {
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
	for (int i = 2; i <= n; i++) {
		for (int x : e) {
			if (acc[i] <= (acc[i] ^ x)) continue;
			acc[i] ^= x;
		}
	}
	return calc(n, k, acc);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m, k; cin >> n >> m >> k;
		vector adj(n + 1, vector(0, pair(0, 0)));
		for (int i = 0; i < m; i++) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back(pair(b, c));
			adj[b].push_back(pair(a, c));
		}
		cout << sol(n, m, k, adj) << '\n';
	}
}