#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1) {}
	void update(int i, int x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	int query(int l, int r) const {
		int ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret += tree[l++];
			if (~r & 1) ret += tree[r--];
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int q, auto qs) {
	vector p1(n + 1, -1);
	vector p2(n + 1, -1);
	vector v(q, 0);
	vector buc(q, vector(0, array{ 0, 0, 0 }));
	for (int i = 0; i < q; i++) {
		auto [op, x] = qs[i];
		if (op == 1) {
			if (p1[x] == -1) v[i] = n;
			else if (p1[x] + 1 <= i - 1) buc[i - 1].push_back(array{ 2, p1[x] + 1, i });
			p1[x] = i;
		}
		else {
			if (p2[x] + 1 <= i - 1) buc[i - 1].push_back(array{ 1, p2[x] + 1, i });
			p2[x] = i;
		}
	}
	segtree t1(q);
	segtree t2(q);
	fill(p1.begin(), p1.end(), -1);
	fill(p2.begin(), p2.end(), -1);
	for (int i = 0; i < q; i++) {
		auto [op, x] = qs[i];
		if (op == 1) {
			if (p1[x] != -1) t1.update(p1[x], 0);
			t1.update(i, 1);
			p1[x] = i;
		}
		else {
			if (p2[x] != -1) t2.update(p2[x], 0);
			t2.update(i, 1);
			p2[x] = i;
		}
		for (auto [a, b, c] : buc[i]) {
			if (a == 1) v[c] = t1.query(b, i);
			else v[c] = t2.query(b, i);
		}
	}
	vector ret(q, i64(0));
	i64 acc = 0;
	for (int i = 0; i < q; i++) {
		if (qs[i][0] == 1) acc += v[i];
		else acc -= v[i];
		ret[i] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [op, x] : qs) cin >> op >> x;
	auto res = sol(n, q, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}