#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto adj) {
	vector sz(n, 1);
	vector dep(n, 0);
	vector sp(18, vector(n, 0));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			sp[0][nxt] = cur;
			for (int bit = 1; bit <= 17; bit++) {
				sp[bit][nxt] = sp[bit - 1][sp[bit - 1][nxt]];
			}
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
		}
	};
	rec(rec, 0, -1);
	auto lca = [&](int a, int b) {
		if (dep[a] < dep[b]) swap(a, b);
		for (int bit = 17; bit >= 0; bit--) {
			if (~(dep[a] - dep[b]) >> bit & 1) continue;
			a = sp[bit][a];
		}
		if (a == b) return a;
		for (int bit = 17; bit >= 0; bit--) {
			if (sp[bit][a] == sp[bit][b]) continue;
			a = sp[bit][a];
			b = sp[bit][b];
		}
		return sp[0][a];
	};
	auto ladder = [&](int p, int k) {
		for (int bit = 17; bit >= 0; bit--) {
			if (~k >> bit & 1) continue;
			p = sp[bit][p];
		}
		return p;
	};
	i64 ret = 1;
	int acc = 1;
	for (int i : adj[0]) {
		ret += i64(acc) * sz[i];
		acc += sz[i];
	}
	for (int i = 1, a = 0, b = 0; i < n; i++) {
		int v_ab = lca(a, b);
		int v_ai = lca(a, i);
		int v_bi = lca(b, i);
		int d_ab = dep[a] + dep[b] - 2 * dep[v_ab];
		int d_ai = dep[a] + dep[i] - 2 * dep[v_ai];
		int d_bi = dep[b] + dep[i] - 2 * dep[v_bi];
		if (d_ab == d_ai + d_bi);
		else if (d_ai == d_ab + d_bi) b = i, v_ab = v_ai;
		else if (d_bi == d_ab + d_ai) a = i, v_ab = v_bi;
		else break;
		int v1 = v_ab != a ? sz[a] : n - sz[ladder(b, dep[b] - dep[a] - 1)];
		int v2 = v_ab != b ? sz[b] : n - sz[ladder(a, dep[a] - dep[b] - 1)];
		ret += i64(v1) * v2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, adj) << '\n';
}