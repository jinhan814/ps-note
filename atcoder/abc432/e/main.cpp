#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (i++; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (i++; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	i64 query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 500'000;
	fenwick t1(sz + 1), t2(sz + 1);
	for (int i = 1; i <= n; i++) {
		t1.update(v[i], 1);
		t2.update(v[i], v[i]);
	}
	auto calc = [&](int a, int b) {
		if (a >= b) return i64(a) * n;
		i64 v1 = t1.query(0, a) * a;
		i64 v2 = t1.query(b, sz) * b;
		i64 v3 = t2.query(a + 1, b - 1);
		return v1 + v2 + v3;
	};
	vector ret(0, i64(0));
	for (auto [op, a, b] : qs) {
		if (op == 1) {
			t1.update(v[a], -1);
			t2.update(v[a], -v[a]);
			v[a] = b;
			t1.update(v[a], 1);
			t2.update(v[a], v[a]);
		}
		else {
			ret.push_back(calc(a, b));
		}
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
	for (i64 x : res) cout << x << '\n';
}