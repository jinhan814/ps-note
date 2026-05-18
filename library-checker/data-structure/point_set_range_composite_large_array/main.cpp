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
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	node query(int l, int r) const {
		node res_l, res_r;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = res_l + tree[l++];
			if (~r & 1) res_r = tree[r--] + res_r;
		}
		return res_l + res_r;
	}
private:
	int sz;
	vector<node> tree;
};

auto sol = [](int n, int q, auto qs) {
	vector cand(0, 0);
	for (auto [op, a, b, c] : qs) {
		if (op != 0) continue;
		cand.push_back(a);
	}
	sort(cand.begin(), cand.end());
	cand.erase(unique(cand.begin(), cand.end()), cand.end());
	segtree tree(cand.size());
	vector ret(0, 0);
	for (auto [op, a, b, c] : qs) {
		if (op == 0) {
			int p = lower_bound(cand.begin(), cand.end(), a) - cand.begin();
			tree.update(p, node(b, c));
		}
		else {
			int p1 = lower_bound(cand.begin(), cand.end(), a) - cand.begin();
			int p2 = upper_bound(cand.begin(), cand.end(), b - 1) - cand.begin() - 1;
			int res = c;
			if (p1 <= p2) res = tree.query(p1, p2).query(c);
			ret.push_back(res);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0, 0, 0 });
	for (auto& [op, a, b, c] : qs) cin >> op >> a >> b >> c;
	auto res = sol(n, q, qs);
	for (int x : res) cout << x << '\n';
}