#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1 | 1) + 1), tree(sz << 1, 1 << 30) {}
	void update(int i, int x) {
		--i |= sz;
		do tree[i] = min(tree[i], x); while (i >>= 1);
	}
	int query(int l, int r) const {
		if (l > r) return 1 << 30;
		int ret = 1 << 30;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int m, int q, auto v, auto qs) {
	vector buc1(n + 1, vector(0, 0));
	vector buc2(n + 1, vector(0, 0));
	segtree tree(n);
	map cnt{ pair(pair(0, 0), 0) }; cnt.clear();
	for (auto [a, b] : v) {
		buc1[a].push_back(b);
		buc2[b].push_back(a);
		tree.update(a, b);
		cnt[pair(a, b)]++;
	}
	for (int i = 1; i <= n; i++) {
		sort(buc1[i].begin(), buc1[i].end());
		sort(buc2[i].begin(), buc2[i].end());
	}
	vector ret(q, false);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		int val = 0;
		if (cnt.count(pair(a, b))) val = cnt[pair(a, b)];
		if (val == 0) {
			auto it1 = upper_bound(buc1[a].begin(), buc1[a].end(), b);
			auto it2 = lower_bound(buc2[b].begin(), buc2[b].end(), a);
			bool f1 = it1 != buc1[a].begin() && *prev(it1) >= a;
			bool f2 = it2 != buc2[b].end() && *it2 <= b;
			if (f1 && f2 && *it2 <= *prev(it1) + 1) ret[i] = true;
			else ret[i] = false;
		}
		else if (val == 1) {
			auto it1 = upper_bound(buc1[a].begin(), buc1[a].end(), b);
			auto it2 = lower_bound(buc2[b].begin(), buc2[b].end(), a);
			if (it1 - buc1[a].begin() >= 2) ret[i] = true;
			else if (buc2[b].end() - it2 >= 2) ret[i] = true;
			else if (tree.query(a + 1, b - 1) <= b) ret[i] = true;
			else ret[i] = false;
		}
		else {
			ret[i] = true;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0 });
	for (int i = 0; i < m; i++) cin >> v[i][0] >> v[i][1];
	int q; cin >> q;
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, m, q, v, qs);
	for (int i = 0; i < q; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}