#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] ^= x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret ^= tree[i];
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
	vector c(n + 1, i64(0));
	for (int i = 1; i <= n; i++) {
		c[i] = uniform_int_distribution(i64(0), (i64(1) << 60) - 1)(rd);
	}
	vector buc(n + 1, vector(0, 0));
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		buc[a].push_back(i);
	}
	vector ret(q, false);
	fenwick tree(2 * n);
	for (int l = 1, r = 1; l <= n; l++) {
		while (r <= n) {
			auto [a, b] = v[r];
			if (tree.query(a) != tree.query(b)) break;
			tree.update(a, c[r]);
			tree.update(b + 1, c[r]);
			r++;
		}
		for (int i : buc[l]) {
			auto [a, b] = qs[i];
			ret[i] = b < r;
		}
		auto [a, b] = v[l];
		tree.update(a, c[l]);
		tree.update(b + 1, c[l]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, array{ 0, 0 });
	vector qs(q, pair(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}