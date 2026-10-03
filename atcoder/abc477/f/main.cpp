#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int m, int q, auto v, auto qs) {
	vector buc(n + 1, vector(0, array{ 0, 0, 0, 0 }));
	for (int i = 0; i < q; i++) {
		auto [a, b, c, d] = qs[i];
		buc[b].push_back(array{ c, d, i, 1 });
		buc[a - 1].push_back(array{ c, d, i, -1 });
	}
	fenwick a(m), b(m);
	vector ret(q, i64(0));
	for (int i = 1; i <= n; i++) {
		a.update(v[i][0], 1);
		b.update(v[i][0], 1 - v[i][0]);
		a.update(v[i][1] + 1, -1);
		b.update(v[i][1] + 1, v[i][1]);
		for (auto [l, r, p, d] : buc[i]) {
			i64 v1 = a.query(l - 1) * (l - 1) + b.query(l - 1);
			i64 v2 = a.query(r) * r + b.query(r);
			ret[p] += (v2 - v1) * d;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector v(n + 1, array{ 0, 0 });
	vector qs(q, array{ 0, 0, 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	for (auto& [a, b, c, d] : qs) cin >> a >> b >> c >> d;
	auto res = sol(n, m, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}