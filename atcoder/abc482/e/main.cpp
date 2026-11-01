#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v, auto adj) {
	vector dep(n + 1, 0);
	vector par(n + 1, -1);
	auto rec = [&](const auto& self, int cur, int prv) -> int {
		int ret = cur;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			int i = self(self, nxt, cur);
			if (dep[ret] < dep[i]) ret = i;
		}
		return ret;
	};
	int x = rec(rec, 1, -1);
	dep[x] = 0;
	int p = rec(rec, x, -1);
	int d = dep[p];
	for (int i = 0; i < d / 2; i++) p = par[p];
	auto calc = [&](int i, int p, int d) {
		vector ret(0, 0);
		auto rec = [&](const auto& self, int cur, int prv, int dep) -> void {
			if (dep == d) ret.push_back(v[cur]);
			for (int nxt : adj[cur]) if (nxt != prv) self(self, nxt, cur, dep + 1);
		};
		rec(rec, i, p, 1);
		return ret;
	};
	if (d % 2 == 0) {
		i64 ret = 0;
		vector c(n + 1, 0);
		for (int i : adj[p]) {
			auto buc = calc(i, p, d / 2);
			for (int x : buc) ret += c[x];
			for (int x : buc) c[x]++;
		}
		return ret;
	}
	else {
		i64 ret = 0;
		vector c(n + 1, 0);
		for (int x : calc(p, par[p], d / 2 + 1)) c[x]++;
		for (int x : calc(par[p], p, d / 2 + 1)) ret += c[x];
		return ret;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v, adj) << '\n';
}