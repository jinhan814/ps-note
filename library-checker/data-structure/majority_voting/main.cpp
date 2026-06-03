#include <bits/stdc++.h>
using namespace std;

struct node {
	int cnt, val;
	node() : cnt(0), val(-1) {}
	node(int x) : cnt(1), val(x) {}
	node(int cnt, int val) : cnt(cnt), val(val) {}
	node operator+ (const node& x) const {
		if (val == x.val) return node(cnt + x.cnt, val);
		if (cnt == x.cnt) return node();
		if (cnt > x.cnt) return node(cnt - x.cnt, val);
		return node(x.cnt - cnt, x.val);
	}
};

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, node x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node ret;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = ret + tree[l++];
			if (~r & 1) ret = ret + tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<node> tree;
};

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

auto sol = [](int n, int q, auto v, auto qs) {
	vector c(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		c.push_back(pair(v[i], i));
	}
	for (auto [op, a, b] : qs) {
		if (op != 0) continue;
		c.push_back(pair(b, a));
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	segtree t1(n);
	fenwick t2(c.size());
	for (int i = 0; i < n; i++) {
		t1.update(i, node(v[i]));
		t2.update(lower_bound(c.begin(), c.end(), pair(v[i], i)) - c.begin() + 1, 1);
	}
	auto update = [&](int i, int x) {
		t2.update(lower_bound(c.begin(), c.end(), pair(v[i], i)) - c.begin() + 1, -1);
		v[i] = x;
		t1.update(i, node(v[i]));
		t2.update(lower_bound(c.begin(), c.end(), pair(v[i], i)) - c.begin() + 1, 1);
	};
	auto query = [&](int l, int r) {
		int val = t1.query(l, r).val;
		if (val == -1) return -1;
		int p1 = lower_bound(c.begin(), c.end(), pair(val, l)) - c.begin() + 1;
		int p2 = upper_bound(c.begin(), c.end(), pair(val, r)) - c.begin();
		int cnt = t2.query(p1, p2);
		if (cnt <= (r - l + 1) / 2) return -1;
		return val;
	};
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 0) update(a, b);
		else ret.push_back(query(a, b - 1));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}