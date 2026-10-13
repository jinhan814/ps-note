#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto e) {
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n - 1; i++) {
		auto [a, b] = e[i];
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector par(n + 1, 0);
	vector sz(n + 1, 1);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			par[nxt] = cur;
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
		}
	};
	rec(rec, 1, 0);
	vector ret(n + 1, i64(0));
	for (int i = 1; i <= n - 1; i++) {
		auto [a, b] = e[i];
		if (par[a] == b) swap(a, b);
		if (2 * sz[b] >= n) ret[b] += i;
		else ret[1] += i, ret[b] -= i;
	}
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			ret[nxt] += ret[cur];
			self(self, nxt, cur);
		}
	};
	dfs(dfs, 1, 0);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector e(n, array{ 0, 0 });
	for (int i = 1; i <= n - 1; i++) cin >> e[i][0] >> e[i][1];
	auto res = sol(n, e);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}