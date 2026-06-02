#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	node() {
		len = l_len = r_len = 0;
		l_c = r_c = 0;
		l_val = r_val = 0;
		flag = true;
	}
	node(i64 val, int c) {
		len = l_len = r_len = 1;
		l_c = r_c = c;
		l_val = r_val = val;
		flag = false;
	}
	node operator+ (const node& x) const {
		if (flag) return x;
		if (x.flag) return *this;
		node ret;
		ret.len = len + x.len;
		ret.l_len = l_len;
		ret.r_len = x.r_len;
		ret.l_c = l_c;
		ret.r_c = x.r_c;
		ret.l_val = l_val;
		ret.r_val = x.r_val;
		if (l_len == len && r_c == x.l_c) {
			ret.l_len += x.l_len;
			ret.l_val += x.l_val;
		}
		if (x.r_len == x.len && r_c == x.l_c) {
			ret.r_len += r_len;
			ret.r_val += r_val;
		}
		ret.flag = false;
		return ret;
	}
	i64 get_val() const {
		return l_val;
	}
	int get_len() const {
		return r_len;
	}
private:
	int len, l_len, r_len;
	int l_c, r_c;
	i64 l_val, r_val;
	bool flag;
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node res_l, res_r;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return res_l + res_r;
	}
private:
	int sz;
	vector<node> tree;
};

auto get_hld = [](auto adj) {
	int n = adj.size() - 1;
	vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
	vector in(n + 1, 0), rin(n + 1, 0), top(n + 1, 0), bot(n + 1, 0);
	int ord = 0;
	auto dfs1 = [&](const auto& self, int cur) -> void {
		for (int& nxt : adj[cur]) {
			adj[nxt].erase(find(adj[nxt].begin(), adj[nxt].end(), cur));
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			self(self, nxt);
			sz[cur] += sz[nxt];
			if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
		}
	};
	auto dfs2 = [&](const auto& self, int cur) -> void {
		in[cur] = ++ord;
		rin[ord] = cur;
		for (int nxt : adj[cur]) {
			top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
			self(self, nxt);
		}
		bot[cur] = adj[cur].size() ? bot[adj[cur][0]] : cur;
	};
	dfs1(dfs1, 1);
	dfs2(dfs2, top[1] = 1);
	return tuple(dep, par, in, rin, top, bot);
};

auto sol = [](int n, int q, auto v, auto c, auto adj, auto qs) {
	auto [dep, par, in, rin, top, bot] = get_hld(adj);
	segtree tree(n);
	vector d(n + 1, array{ i64(0), i64(0) });
	for (int i = n; i >= 1; i--) {
		int p = rin[i];
		tree.update(in[p], node(v[p] + d[p][c[p]], c[p]));
		if (p != 1 && top[p] == p) {
			d[par[p]][c[p]] += tree.query(in[p], in[bot[p]]).get_val();
		}
	}
	auto update = [&](int i, i64 a, int b) {
		bool flag = false;
		while (top[i] != 1) {
			d[par[top[i]]][c[top[i]]] -= tree.query(in[top[i]], in[bot[i]]).get_val();
			if (!flag) v[i] = a, c[i] = b, flag = true;
			tree.update(in[i], node(v[i] + d[i][c[i]], c[i]));
			d[par[top[i]]][c[top[i]]] += tree.query(in[top[i]], in[bot[i]]).get_val();
			i = par[top[i]];
		}
		if (!flag) v[i] = a, c[i] = b, flag = true;
		tree.update(in[i], node(v[i] + d[i][c[i]], c[i]));
	};
	auto query = [&](int i) {
		while (1) {
			int len = tree.query(in[top[i]], in[i]).get_len();
			i = rin[in[i] - len + 1];
			if (i != 1 && top[i] == i && c[par[i]] == c[i]) i = par[i];
			else break;
		}
		return tree.query(in[i], in[bot[i]]).get_val();
	};
	vector ret(0, i64(0));
	for (auto [op, a, b] : qs) {
		if (op == 1) update(a, v[a], !c[a]);
		if (op == 2) update(a, v[a] + b, c[a]);
		if (op == 3) ret.push_back(query(a));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, i64(0));
	vector c(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (auto& [op, a, b] : qs) {
		cin >> op >> a;
		if (op == 2) cin >> b;
	}
	auto res = sol(n, q, v, c, adj, qs);
	for (i64 x : res) cout << x << '\n';
}