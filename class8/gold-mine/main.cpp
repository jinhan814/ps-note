#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct node {
	i64 l, r, s, mx;
	node() : node(0) {}
	node(i64 x) : l(x), r(x), s(x), mx(x) {}
	node operator+ (const node& x) const {
		node ret;
		ret.l = max(l, s + x.l);
		ret.r = max(r + x.s, x.r);
		ret.s = s + x.s;
		ret.mx = max({ mx, x.mx, r + x.l });
		return ret;
	}
};

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1) {}
	void update(int i, i64 x) {
		--i |= sz;
		tree[i] = node(tree[i].mx + x);
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	i64 query() const {
		return tree[1].mx;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, auto v) {
	vector c(0, 0);
	for (auto [x, y, k] : v) c.push_back(y);
	sort(v.begin(), v.end());
	sort(c.begin(), c.end());
	for (auto& [x, y, k] : v) {
		auto it = lower_bound(c.begin(), c.end(), y);
		y = it - c.begin() + 1;
	}
	i64 res = 0;
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i][0] == v[j][0]) j++;
		segtree tree(c.size());
		for (int l = i, r = i; l < n; l = r) {
			while (r < n && v[l][0] == v[r][0]) r++;
			for (int k = l; k < r; k++) tree.update(v[k][1], v[k][2]);
			res = max(res, tree.query());
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [x, y, k] : v) cin >> x >> y >> k;
	cout << sol(n, v) << '\n';
}