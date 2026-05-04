#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1 | 1) + 1), tree(sz << 1, -(i64(1) << 60)) {}
	void update(int i, i64 x) {
		i |= sz;
		do tree[i] = max(tree[i], x); while (i >>= 1);
	}
	i64 query(int l, int r) const {
		i64 ret = -(i64(1) << 60);
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int l, int r, int a, int b, auto v) {
	vector c(1, l % a);
	for (int i = 0; i < n; i++) c.push_back(v[i][0] % a);
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	segtree tree(c.size());
	auto update = [&](int i, i64 x) {
		i = lower_bound(c.begin(), c.end(), i) - c.begin();
		tree.update(i, x);
	};
	auto query = [&](int l, int r) {
		if (l > r) return -(i64(1) << 60);
		l = lower_bound(c.begin(), c.end(), l) - c.begin();
		r = upper_bound(c.begin(), c.end(), r) - c.begin() - 1;
		return tree.query(l, r);
	};
	vector dp(n, i64(0));
	update(l % a, i64(l) / a * b);
	for (int i = 0; i < n; i++) {
		i64 pos = (v[i][0] + a - 1) % a;
		i64 bias = v[i][1] - i64(v[i][0] + a - 1) / a * b;
		i64 v1 = query(0, pos) + bias;
		i64 v2 = query(pos + 1, a - 1) + b + bias;
		dp[i] = max(v1, v2);
		update(v[i][0] % a, dp[i] + i64(v[i][0]) / a * b);
	}
	i64 ret = -i64(r - l + a - 1) / a * b;
	for (int i = 0; i < n; i++) {
		i64 val = dp[i] - i64(r - v[i][0] + a - 1) / a * b;
		ret = max(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, l, r, a, b; cin >> l >> r >> a >> b >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, l, r, a, b, v) << '\n';
}