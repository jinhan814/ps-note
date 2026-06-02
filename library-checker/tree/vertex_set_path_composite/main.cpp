#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

struct node {
	node() : a(1), b(0) {}
	node(int a, int b) : a(a), b(b) {}
	node operator+(const node& x) const {
		node ret;
		ret.a = mul(a, x.a);
		ret.b = add(mul(b, x.a), x.b);
		return ret;
	}
	int query(int x) const {
		return add(mul(a, x), b);
	}
private:
	int a, b;
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
	int n = adj.size();
	vector sz(n, 1), dep(n, 0), par(n, 0);
	vector in(n, 0), top(n, 0);
	int ord = 0;
	auto dfs1 = [&](auto& self, int cur) -> void {
		for (int& nxt : adj[cur]) {
			adj[nxt].erase(find(adj[nxt].begin(), adj[nxt].end(), cur));
			dep[nxt] = dep[cur] + 1;
			par[nxt] = cur;
			self(self, nxt);
			sz[cur] += sz[nxt];
			if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
		}
	};
	auto dfs2 = [&](auto& self, int cur) -> void {
		in[cur] = ++ord;
		for (int nxt : adj[cur]) {
			top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
			self(self, nxt);
		}
	};
	dfs1(dfs1, 0);
	dfs2(dfs2, 0);
	return tuple(dep, par, in, top);
};

auto sol = [](int n, int q, auto v, auto adj, auto qs) {
	auto [dep, par, in, top] = get_hld(adj);
	segtree t1(n), t2(n);
	for (int i = 0; i < n; i++) {
		t1.update(in[i], node(v[i][0], v[i][1]));
		t2.update(n + 1 - in[i], node(v[i][0], v[i][1]));
	}
	auto update = [&](int i, int a, int b) {
		t1.update(in[i], node(a, b));
		t2.update(n + 1 - in[i], node(a, b));
	};
	auto query = [&](int a, int b, int x) {
		node res_l, res_r;
		while (top[a] != top[b]) {
			if (dep[top[a]] > dep[top[b]]) {
				res_l = res_l + t2.query(n + 1 - in[a], n + 1 - in[top[a]]);
				a = par[top[a]];
			}
			else {
				res_r = t1.query(in[top[b]], in[b]) + res_r;
				b = par[top[b]];
			}
		}
		if (dep[a] > dep[b]) {
			res_l = res_l + t2.query(n + 1 - in[a], n + 1 - in[b]);
		}
		else {
			res_r = t1.query(in[a], in[b]) + res_r;
		}
		return (res_l + res_r).query(x);
	};
	vector ret(0, 0);
	for (auto [op, a, b, c] : qs) {
		if (op == 0) update(a, b, c);
		else ret.push_back(query(a, b, c));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, array{ 0, 0 });
	vector adj(n, vector(0, 0));
	vector qs(q, array{ 0, 0, 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (auto& [op, a, b, c] : qs) cin >> op >> a >> b >> c;
	auto res = sol(n, q, v, adj, qs);
	for (int x : res) cout << x << '\n';
}