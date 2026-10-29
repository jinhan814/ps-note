#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, i64(0));
	auto update = [&](int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	};
	auto query1 = [&](int i, i64 x) {
		--i |= sz;
		while (tree[i] < x) {
			if ((i & i + 1) == 0) return n + 1;
			x -= tree[i++];
			if (~i & 1) i >>= 1;
		}
		while (i < sz) {
			i <<= 1;
			if (tree[i] < x) x -= tree[i++];
		}
		return i - sz + 1;
	};
	auto query2 = [&](int i, i64 x) {
		--i |= sz;
		while (tree[i] < x) {
			if (i == (i & -i)) return 0;
			x -= tree[i--];
			if (i & 1) i >>= 1;
		}
		while (i < sz) {
			i = i << 1 | 1;
			if (tree[i] < x) x -= tree[i--];
		}
		return i - sz + 1;
	};
	for (int i = 1; i <= n; i++) update(i, v[i]);
	vector ret(0, 0);
	for (auto [op, a, b] : qs) {
		if (op == 1) update(a, b);
		if (op == 2) ret.push_back(query1(a, b));
		if (op == 3) ret.push_back(query2(a, b));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, tuple(0, 0, i64(0)));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, v, qs);
	for (i64 x : res) cout << x << '\n';
}