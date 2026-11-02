#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, pair(i64(0), i64(-1)));
	auto merge = [](auto a, auto b) {
		if (a.second == -1 && b.second == -1) return pair(a.first + b.first, i64(-1));
		if (a.second == -1) return pair(a.first + b.first, b.second);
		if (b.second == -1) return pair(a.first, a.second + b.first);
		return pair(a.first + a.second + b.first, b.second);
	};
	auto update = [&](int i, int x) {
		--i |= sz;
		tree[i].first = x;
		tree[i].second = x == 0 ? 0 : -1;
		while (i >>= 1) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	};
	auto query = [&](int l, int r, i64 x) {
		pair res_l(i64(0), i64(-1));
		pair res_r(i64(0), i64(-1));
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res_l = merge(res_l, tree[l++]);
			if (~r & 1) res_r = merge(tree[r--], res_r);
		}
		auto [a, b] = merge(res_l, res_r);
		x += a;
		if (b != -1) x = x % mod + b;
		return x;
	};
	for (int i = 1; i <= n; i++) update(i, v[i]);
	vector ret(0, i64(0));
	for (auto [op, a, b, c] : qs) {
		if (op == 1) update(a, b);
		else ret.push_back(query(a, b, c));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, tuple(0, 0, 0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b, c] : qs) {
		cin >> op >> a >> b;
		if (op == 2) cin >> c;
	}
	auto res = sol(n, q, v, qs);
	for (i64 x : res) cout << x << '\n';
}