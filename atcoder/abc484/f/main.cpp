#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, -1);
	auto merge = [&](int a, int b) {
		if (a == -1) return b;
		if (b == -1) return a;
		if (a == b) return a;
		return -2;
	};
	auto update = [&](int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	};
	auto query = [&](int l, int r) {
		int ret = -1;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = merge(ret, tree[l++]);
			if (~r & 1) ret = merge(ret, tree[r--]);
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) update(i, v[i]);
	vector ret(0, false);
	for (auto [op, a, b] : qs) {
		if (op == 1) update(a, b);
		else ret.push_back(query(a, b) != -2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, qs);
	for (bool x : res) cout << (x ? "Yes" : "No") << '\n';
}