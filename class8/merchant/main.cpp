#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, -(1 << 30)) {}
	void set(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	void update(int i, int x) {
		--i |= sz;
		do tree[i] = max(tree[i], x); while (i >>= 1);
	}
	int query(int l, int r) const {
		int ret = -(1 << 30);
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int a, int b, int s, auto v) {
	sort(v.begin(), v.end());
	vector dp(n, -(1 << 30)), prv(n, 0);
	segtree tree_l(500'001), tree_r(500'001);
	tree_l.update(s, 0 + b * s);
	tree_r.update(s, 0 - a * s);
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i][0] == v[j][0]) j++;
		for (int cur = i; cur < j; cur++) {
			int x = tree_l.query(1, v[cur][1] - 1) - b * v[cur][1];
			int y = tree_r.query(v[cur][1] + 1, 500'001) + a * v[cur][1];
			int val = max(x, y) + v[cur][2];
			dp[cur] = max(dp[cur], val);
			prv[cur] = tree_l.query(v[cur][1], v[cur][1]);
			tree_l.update(v[cur][1], val + b * v[cur][1]);
		}
		for (int cur = i; cur < j; cur++) {
			tree_l.set(v[cur][1], prv[cur]);
		}
		for (int cur = j - 1; cur >= i; cur--) {
			int x = tree_l.query(1, v[cur][1] - 1) - b * v[cur][1];
			int y = tree_r.query(v[cur][1] + 1, 500'001) + a * v[cur][1];
			int val = max(x, y) + v[cur][2];
			dp[cur] = max(dp[cur], val);
			tree_r.update(v[cur][1], val - a * v[cur][1]);
		}
		for (int cur = i; cur < j; cur++) {
			tree_l.update(v[cur][1], dp[cur] + b * v[cur][1]);
			tree_r.update(v[cur][1], dp[cur] - a * v[cur][1]);
		}
	}
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int val = v[i][1] > s ? a * (v[i][1] - s) : b * (s - v[i][1]);
		ret = max(ret, dp[i] - val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b, s; cin >> n >> a >> b >> s;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [a, b, c] : v) cin >> a >> b >> c;
	int res = sol(n, a, b, s, v);
	cout << res << '\n';
}