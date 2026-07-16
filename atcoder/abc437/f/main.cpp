#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1, -(1 << 30)) {}
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
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

auto sol = [](int n, int q, auto v, auto qs) {
	segtree t1(n), t2(n), t3(n), t4(n);
	for (int i = 1; i <= n; i++) {
		t1.update(i, v[i][0] + v[i][1]);
		t2.update(i, v[i][0] - v[i][1]);
		t3.update(i, -v[i][0] + v[i][1]);
		t4.update(i, -v[i][0] - v[i][1]);
	}
	vector ret(0, i64(0));
	for (auto [op, a, b, c, d] : qs) {
		if (op == 1) {
			v[a][0] = b;
			v[a][1] = c;
			t1.update(a, b + c);
			t2.update(a, b - c);
			t3.update(a, -b + c);
			t4.update(a, -b - c);
		}
		else {
			i64 res = 0;
			res = max(res, i64(t1.query(a, b)) - c - d);
			res = max(res, i64(t2.query(a, b)) - c + d);
			res = max(res, i64(t3.query(a, b)) + c - d);
			res = max(res, i64(t4.query(a, b)) + c + d);
			ret.push_back(res);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, array{ 0, 0 });
	vector qs(q, array{ 0, 0, 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	for (auto& [op, a, b, c, d] : qs) {
		cin >> op >> a >> b >> c;
		if (op == 2) cin >> d;
	}
	auto res = sol(n, q, v, qs);
	for (i64 x : res) cout << x << '\n';
}