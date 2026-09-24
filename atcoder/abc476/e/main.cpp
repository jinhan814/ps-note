#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, array{ 0, 0 });
	auto merge = [&](auto a, auto b) {
		int v1 = !b[0] || a[0] && v[a[0]] < v[b[0]] ? a[0] : b[0];
		int v2 = !b[1] || a[1] && v[a[1]] > v[b[1]] ? a[1] : b[1];
		return array{ v1, v2 };
	};
	auto update = [&](int i) {
		--i |= sz;
		while (i >>= 1) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	};
	auto query = [&](int l, int r) {
		array ret{ 0, 0 };
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = merge(ret, tree[l++]);
			if (~r & 1) ret = merge(ret, tree[r--]);
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) {
		tree[i - 1 | sz] = array{ i, i };
		update(i);
	}
	for (auto [l, r] : qs) {
		auto [a, b] = query(l, r);
		swap(v[a], v[b]);
		update(a);
		update(b);
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}