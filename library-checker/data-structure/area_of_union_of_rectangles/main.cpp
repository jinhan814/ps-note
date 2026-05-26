#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct info {
	int mn, cnt;
	info() : mn(0), cnt(0) {}
	info(int a, int b) : mn(a), cnt(b) {}
	info operator+ (const info& x) const {
		if (mn < x.mn) return *this;
		if (mn > x.mn) return x;
		return info(mn, cnt + x.cnt);
	}
};

struct segtree {
	segtree(int n) : sz(n), tree(1, info(0, n)), link(1, pair(-1, -1)), lazy(1) {}
	void update(int l, int r, int x) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> void {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return;
			if (l <= node_l && node_r <= r) {
				lazy[node] = x;
				push(node, node_l, node_r);
				return;
			}
			int mid = (node_l + node_r) >> 1;
			self(self, link[node].first, node_l, mid);
			self(self, link[node].second, mid + 1, node_r);
			tree[node] = tree[link[node].first] + tree[link[node].second];
		};
		rec(rec, 0, 1, sz);
	}
	info query(int l, int r) {
		auto rec = [&](const auto& self, int node, int node_l, int node_r) -> info {
			push(node, node_l, node_r);
			if (node_r < l || r < node_l) return info(1 << 30, 0);
			if (l <= node_l && node_r <= r) return tree[node];
			int mid = (node_l + node_r) >> 1;
			info r1 = self(self, link[node].first, node_l, mid);
			info r2 = self(self, link[node].second, mid + 1, node_r);
			return r1 + r2;
		};
		return rec(rec, 0, 1, sz);
	}
private:
	int sz;
	vector<info> tree;
	vector<pair<int, int>> link;
	vector<int> lazy;
	void push(int i, int l, int r) {
		if (l != r) {
			int mid = (l + r) >> 1;
			if (link[i].first == -1) {
				tree.push_back(info(0, mid - l + 1));
				link.push_back(pair(-1, -1));
				lazy.push_back(0);
				link[i].first = tree.size() - 1;
			}
			if (link[i].second == -1) {
				tree.push_back(info(0, r - mid));
				link.push_back(pair(-1, -1));
				lazy.push_back(0);
				link[i].second = tree.size() - 1;
			}
			lazy[link[i].first] += lazy[i];
			lazy[link[i].second] += lazy[i];
		}
		tree[i].mn += lazy[i];
		lazy[i] = 0;
	}
};

auto sol = [](int n, auto v) {
	vector buc(0, array{ 0, 0, 0, 0 });
	for (auto [x1, y1, x2, y2] : v) {
		buc.push_back(array{ x1, 1, y1 + 1, y2 });
		buc.push_back(array{ x2, -1, y1 + 1, y2 });
	}
	sort(buc.begin(), buc.end());
	i64 ret = 0;
	segtree tree(1'000'000'000);
	for (int i = 0, j = 0; i < buc.size(); i = j) {
		while (j < buc.size() && buc[i][0] == buc[j][0]) {
			auto [x, d, l, r] = buc[j++];
			tree.update(l, r, d);
		}
		if (j < buc.size()) {
			info res = tree.query(1, 1'000'000'000);
			i64 v1 = buc[j][0] - buc[i][0];
			i64 v2 = 1'000'000'000;
			if (res.mn == 0) v2 -= res.cnt;
			ret += v1 * v2;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0, 0 });
	for (auto& [a, b, c, d] : v) cin >> a >> b >> c >> d;
	cout << sol(n, v) << '\n';
}