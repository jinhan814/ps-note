#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto adj) {
	vector dep(n + 1, 0), in(n + 1, 0), out(n + 1, 0);
	vector dp(n + 1, i64(0));
	vector sp(19, vector(n + 1, 0));
	fenwick tree(n);
	int ord = 0;
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		in[cur] = ++ord;
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + 1;
			dp[nxt] = dp[cur] + cost;
			sp[0][nxt] = cur;
			for (int bit = 1; bit <= 18; bit++) {
				sp[bit][nxt] = sp[bit - 1][sp[bit - 1][nxt]];
				if (sp[bit][nxt] == 0) break;
			}
			self(self, nxt, cur);
		}
		out[cur] = ord;
	};
	rec(rec, 1, -1);
	auto lca = [&](int i, int j) {
		if (dep[i] < dep[j]) swap(i, j);
		for (int bit = 18; bit >= 0; bit--) {
			if (~(dep[i] - dep[j]) >> bit & 1) continue;
			i = sp[bit][i];
		}
		if (i == j) return i;
		for (int bit = 18; bit >= 0; bit--) {
			if (sp[bit][i] == sp[bit][j]) continue;
			i = sp[bit][i];
			j = sp[bit][j];
		}
		return sp[0][i];
	};
	auto dist = [&](int i, int j) {
		int u = lca(i, j);
		return dp[i] + dp[j] - 2 * dp[u];
	};
	vector ret(n + 1, i64(0));
	i64 acc = 0;
	int p = 1;
	for (int i = 1; i <= n; i++) {
		tree.update(in[i], 1);
		acc += dist(p, i);
		if (i % 2 == 1) {
			int a = p, b = i;
			for (int bit = 18; bit >= 0; bit--) {
				int na = sp[bit][a];
				int nb = sp[bit][b];
				if (na != 0 && tree.query(in[na], out[na]) <= i / 2) a = na;
				if (nb != 0 && tree.query(in[nb], out[nb]) <= i / 2) b = nb;
			}
			if (tree.query(in[a], out[a]) <= i / 2) a = sp[0][a];
			if (tree.query(in[b], out[b]) <= i / 2) b = sp[0][b];
			if (dep[a] < dep[b]) swap(a, b);
			acc -= dist(p, a);
			p = a;
		}
		ret[i] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 2; i <= n; i++) {
		int p, x; cin >> p >> x;
		adj[i].push_back(pair(p, x));
		adj[p].push_back(pair(i, x));
	}
	auto res = sol(n, adj);
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}