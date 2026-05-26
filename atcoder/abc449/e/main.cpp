#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(int k) const {
		int ret = 0;
		for (int bit = 18; bit >= 0; bit--) {
			int p = ret | 1 << bit;
			if (p <= sz && tree[p] < k) k -= tree[ret = p];
		}
		return ret + 1;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int m, int q, auto v, auto qs) {
	vector ret(q, -1);
	vector cand(0, 0);
	for (int i = 0; i < q; i++) {
		i64 x = qs[i];
		if (x <= n) ret[i] = v[x - 1];
		else cand.push_back(i);
	}
	sort(cand.begin(), cand.end(), [&](int i, int j) {
		return qs[i] < qs[j];
	});
	vector cnt(m + 1, 0);
	for (int i = 0; i < n; i++) cnt[v[i]]++;
	vector buc(m, 0);
	iota(buc.begin(), buc.end(), 1);
	sort(buc.begin(), buc.end(), [&](int i, int j) {
		return cnt[i] < cnt[j];
	});
	fenwick tree(m);
	i64 acc = n;
	int p = 0;
	for (int l = 0, r = 0; l < m; l = r) {
		while (r < m && buc[l] == buc[r]) {
			tree.update(buc[r], 1);
			r++;
		}
		int v1 = tree.query(m);
		i64 v2 = 2e12;
		if (r < m) v2 = cnt[buc[r]] - cnt[buc[l]];
		i64 nacc = acc + v1 * v2;
		while (p < cand.size() && qs[cand[p]] <= nacc) {
			int val = (qs[cand[p]] - acc) % v1;
			if (val == 0) val = v1;
			ret[cand[p]] = tree.kth(val);
			p++;
		}
		acc = nacc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int q; cin >> q;
	vector qs(q, i64(0));
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, m, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}