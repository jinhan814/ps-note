#include <bits/stdc++.h>
using namespace std;

constexpr int mask = (1 << 30) - 1;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, array{ 0, 0 });
	auto merge = [](auto a, auto b) {
		int v1 = (~a[0] & b[0]) | (a[0] & b[1]);
		int v2 = (~a[1] & b[0]) | (a[1] & b[1]);
		return array{ v1, v2 };
	};
	auto update = [&](int i, int x) {
		v[i] = x;
		tree[--i |= sz] = array{ mask, mask ^ x };
		while (i >>= 1) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	};
	auto query = [&](int l, int r) {
		int x = v[l];
		array res_l{ 0, mask }, res_r{ 0, mask };
		for (l += sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = merge(res_l, tree[l++]);
			if (~r & 1) res_r = merge(tree[r--], res_r);
		}
		auto res = merge(res_l, res_r);
		return (~x & res[0]) | (x & res[1]);
	};
	for (int i = 1; i <= n; i++) update(i, v[i]);
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) update(a, b);
		else ret.push_back(query(a, b));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, tuple(0, 0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}