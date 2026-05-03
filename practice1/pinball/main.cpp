#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1 | 1) + 1), tree(sz << 1, i64(1) << 60) {}
	void update(int i, i64 x) {
		--i |= sz;
		do tree[i] = min(tree[i], x); while (i >>= 1);
	}
	i64 query(int l, int r) const {
		i64 ret = i64(1) << 60;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int m, auto v) {
	vector buc{ 1, m };
	for (auto [a, b, c, d] : v) {
		buc.push_back(a);
		buc.push_back(b);
		buc.push_back(c);
	}
	sort(buc.begin(), buc.end());
	buc.erase(unique(buc.begin(), buc.end()), buc.end());
	for (auto& [a, b, c, d] : v) {
		a = lower_bound(buc.begin(), buc.end(), a) - buc.begin() + 1;
		b = lower_bound(buc.begin(), buc.end(), b) - buc.begin() + 1;
		c = lower_bound(buc.begin(), buc.end(), c) - buc.begin() + 1;
	}
	i64 ret = i64(1) << 60;
	segtree t1(buc.size());
	segtree t2(buc.size());
	t1.update(1, 0);
	t2.update(buc.size(), 0);
	for (auto [a, b, c, d] : v) {
		ret = min(ret, t1.query(a, b) + t2.query(a, b) + d);
		t1.update(c, t1.query(a, b) + d);
		t2.update(c, t2.query(a, b) + d);
	}
	if (ret >> 60) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0, 0, 0 });
	for (auto& [a, b, c, d] : v) cin >> a >> b >> c >> d;
	cout << sol(n, m, v) << '\n';
}