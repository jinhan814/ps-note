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
	i64 query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	int sz = 1 << (__lg(n - 1 | 1) + 1);
	vector buc(sz << 1, vector(0, 0));
	for (int i = 0; i < n; i++) buc[sz | i].push_back(v[i]);
	for (auto [i, x, l, r, k] : qs) buc[sz | i].push_back(x);
	for (int i = sz; i < sz << 1; i++) {
		sort(buc[i].begin(), buc[i].end());
		buc[i].erase(unique(buc[i].begin(), buc[i].end()), buc[i].end());
	}
	for (int i = sz - 1; i >= 1; i--) {
		const auto& v1 = buc[i << 1];
		const auto& v2 = buc[i << 1 | 1];
		auto push = [&](int x) {
			if (buc[i].size() && buc[i].back() == x) return;
			buc[i].push_back(x);
		};
		for (int p1 = 0, p2 = 0; p1 < v1.size() || p2 < v2.size();) {
			if (p2 == v2.size()) push(v1[p1++]);
			else if (p1 == v1.size()) push(v2[p2++]);
			else if (v1[p1] < v2[p2]) push(v1[p1++]);
			else push(v2[p2++]);
		}
	}
	fenwick tree(n);
	vector tree_sum(sz << 1, fenwick(0));
	vector tree_cnt(sz << 1, fenwick(0));
	for (int i = 1; i < sz << 1; i++) {
		tree_sum[i] = fenwick(buc[i].size());
		tree_cnt[i] = fenwick(buc[i].size());
	}
	for (int i = 0; i < n; i++) {
		tree.update(i + 1, v[i]);
		for (int j = i | sz; j; j >>= 1) {
			int p = buc[j].end() - lower_bound(buc[j].begin(), buc[j].end(), v[i]);
			tree_sum[j].update(p, v[i]);
			tree_cnt[j].update(p, 1);
		}
	}
	auto update = [&](int i, int x) {
		if (v[i] == x) return;
		int p = v[i];
		v[i] = x;
		tree.update(i + 1, x - p);
		for (i |= sz; i; i >>= 1) {
			int p1 = buc[i].end() - lower_bound(buc[i].begin(), buc[i].end(), p);
			int p2 = buc[i].end() - lower_bound(buc[i].begin(), buc[i].end(), x);
			tree_sum[i].update(p1, -p);
			tree_sum[i].update(p2, x);
			tree_cnt[i].update(p1, -1);
			tree_cnt[i].update(p2, 1);
		}
	};
	auto query = [&](const auto& tree, int l, int r, int x) {
		i64 ret = 0;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) {
				int p = buc[l].end() - lower_bound(buc[l].begin(), buc[l].end(), x);
				ret += tree[l++].query(p);
			}
			if (~r & 1) {
				int p = buc[r].end() - lower_bound(buc[r].begin(), buc[r].end(), x);
				ret += tree[r--].query(p);
			}
		}
		return ret;
	};
	vector ret(q, 0);
	for (int iter = 0; iter < q; iter++) {
		auto [i, x, l, r, k] = qs[iter];
		update(i, x);
		if (tree.query(l + 1, r + 1) < k) {
			ret[iter] = -1;
		}
		else {
			int lo = 0, hi = buc[1].size();
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				if (query(tree_sum, l, r, buc[1][mid]) >= k) lo = mid;
				else hi = mid;
			}
			i64 acc = query(tree_sum, l, r, buc[1][lo]);
			int cnt = query(tree_cnt, l, r, buc[1][lo]);
			ret[iter] = cnt - (acc - k) / buc[1][lo];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, tuple(0, 0, 0, 0, i64(0)));
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [i, x, l, r, k] : qs) {
		cin >> i >> x >> l >> r >> k;
		i--;
		l--;
		r--;
	}
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}