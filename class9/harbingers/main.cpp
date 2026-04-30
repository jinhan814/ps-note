#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct line {
	line() : a(0), b(0) {}
	line(i64 a, i64 b) : a(a), b(b) {}
	i64 get(int x) const {
		return a * x + b;
	}
private:
	i64 a, b;
};

struct segtree {
	segtree() : tree(1, line(0, 0)), l(1, -1), r(1, -1) {}
	void push(line x) {
		vector buc(0, tuple(0, line(0, 0), 0, 0));
		int lim = tree.size();
		int cnt = 0;
		auto rec = [&](const auto& self, int node, int node_l, int node_r, line hi) -> void {
			if (node < lim) {
				buc.push_back(tuple(node, tree[node], l[node], r[node]));
			}
			line lo = tree[node];
			if (lo.get(node_l) > hi.get(node_l)) {
				swap(lo, hi);
			}
			if (node_r - node_l == 1) {
				tree[node] = lo;
				return;
			}
			if (lo.get(node_r) <= hi.get(node_r)) {
				tree[node] = lo;
				return;
			}
			int mid = (node_l + node_r) >> 1;
			if (lo.get(mid) <= hi.get(mid)) {
				tree[node] = lo;
				if (r[node] == -1) {
					tree.push_back(lo);
					l.push_back(-1);
					r.push_back(-1);
					r[node] = r.size() - 1;
					cnt++;
				}
				self(self, r[node], mid, node_r, hi);
			}
			else {
				tree[node] = hi;
				if (l[node] == -1) {
					tree.push_back(hi);
					l.push_back(-1);
					r.push_back(-1);
					l[node] = l.size() - 1;
					cnt++;
				}
				self(self, l[node], node_l, mid, lo);
			}
		};
		rec(rec, 0, 0, 1 << 30, x);
		data.push_back(pair(buc, cnt));
	}
	void pop() {
		auto [info, cnt] = data.back();
		data.pop_back();
		for (auto [i, x, a, b] : info) {
			tree[i] = x;
			l[i] = a;
			r[i] = b;
		}
		while (cnt--) {
			tree.pop_back();
			l.pop_back();
			r.pop_back();
		}
	}
	i64 query(int x) const {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> i64 {
			if (node_r - node_l == 1) return tree[node].get(x);
			i64 ret = tree[node].get(x);
			int mid = (node_l + node_r) >> 1;
			if (x < mid && l[node] != -1) {
				ret = min(ret, self(self, l[node], node_l, mid));
			}
			if (x >= mid && r[node] != -1) {
				ret = min(ret, self(self, r[node], mid, node_r));
			}
			return ret;
		};
		return rec(rec, 0, 0, 1 << 30);
	}
private:
	vector<line> tree;
	vector<int> l, r;
	vector<pair<vector<tuple<int, line, int, int>>, int>> data;
};

auto sol = [](int n, auto v, auto adj) {
	vector dp(n + 1, i64(0));
	vector dep(n + 1, 0);
	segtree tree;
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		if (cur != 1) {
			dp[cur] = tree.query(v[cur][1]) + v[cur][0] + i64(dep[cur]) * v[cur][1];
			tree.push(line(-dep[cur], dp[cur]));
		}
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			dep[nxt] = dep[cur] + cost;
			self(self, nxt, cur);
		}
		if (cur != 1) {
			tree.pop();
		}
	};
	rec(rec, 1, -1);
	return dp;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	for (int i = 2; i <= n; i++) {
		cin >> v[i][0] >> v[i][1];
	}
	auto res = sol(n, v, adj);
	for (int i = 2; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}