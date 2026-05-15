#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, int x) {
		i |= sz;
		do tree[i] += x; while (i >>= 1);
	}
	int query(int l, int r) const {
		int ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
	int kth(int k) const {
		int ret = 1;
		while (ret < sz) {
			ret <<= 1;
			if (tree[ret] < k) k -= tree[ret++];
		}
		return ret - sz;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	auto c = v;
	for (auto [op, x] : qs) {
		if (op >= 2) continue;
		c.push_back(x);
	}
	c.push_back(0);
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	segtree tree(c.size());
	for (int i = 0; i < n; i++) {
		int p = lower_bound(c.begin(), c.end(), v[i]) - c.begin();
		tree.update(p, 1);
	}
	vector ret(0, 0);
	for (auto [op, x] : qs) {
		if (op == 0) {
			int p = lower_bound(c.begin(), c.end(), x) - c.begin();
			if (tree.query(p, p) == 0) tree.update(p, 1);
		}
		else if (op == 1) {
			int p = lower_bound(c.begin(), c.end(), x) - c.begin();
			if (tree.query(p, p) == 1) tree.update(p, -1);
		}
		else if (op == 2) {
			int res = -1;
			if (x <= tree.query(0, c.size() - 1)) res = c[tree.kth(x)];
			ret.push_back(res);
		}
		else if (op == 3) {
			int p = upper_bound(c.begin(), c.end(), x) - c.begin() - 1;
			int res = 0;
			if (p >= 0) res = tree.query(0, p);
			ret.push_back(res);
		}
		else if (op == 4) {
			int p = upper_bound(c.begin(), c.end(), x) - c.begin() - 1;
			int res = -1;
			if (p >= 0) {
				int cnt = tree.query(0, p);
				if (cnt > 0) res = c[tree.kth(cnt)];
			}
			ret.push_back(res);
		}
		else {
			int p = lower_bound(c.begin(), c.end(), x) - c.begin();
			int res = -1;
			if (p < c.size()) {
				int cnt = 0;
				if (p >= 1) cnt = tree.query(0, p - 1);
				if (tree.query(0, c.size() - 1) - cnt > 0) res = c[tree.kth(cnt + 1)];
			}
			ret.push_back(res);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}