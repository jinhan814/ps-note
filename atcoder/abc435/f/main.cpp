#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	auto f = [&](int i, int j) { return v[i] > v[j] ? i : j; };
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector tree(sz << 1, 0);
	for (int i = 0; i < n; i++) tree[i | sz] = i;
	for (int i = sz - 1; i >= 1; i--) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	auto query = [&](int l, int r) {
		int ret = l;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = f(ret, tree[l++]);
			if (~r & 1) ret = f(ret, tree[r--]);
		}
		return ret;
	};
	auto rec = [&](const auto& self, int l, int r, int p) -> i64 {
		i64 ret = 0;
		if (p > l) {
			int i = query(l, p - 1);
			ret = max(ret, self(self, l, p - 1, i) + (p - i));
		}
		if (p < r) {
			int i = query(p + 1, r);
			ret = max(ret, self(self, p + 1, r, i) + (i - p));
		}
		return ret;
	};
	return rec(rec, 0, n - 1, query(0, n - 1));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}