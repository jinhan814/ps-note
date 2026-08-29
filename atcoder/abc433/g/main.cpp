#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1, 1 << 30) {}
	void update(int i, int x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		if (l > r) return 1 << 30;
		int ret = 1 << 30;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto get_sa = [](string s) {
	int n = s.size();
	int m = max(256, n) + 1;
	vector sa(n, 0), r(n << 1, 0), nr(n << 1, 0);
	vector idx(n, 0), cnt(m, 0);
	for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
	for (int d = 1; d < n; d <<= 1) {
		auto cmp = [&](int a, int b) {
			if (r[a] < r[b]) return true;
			if (r[a] == r[b] && r[a + d] < r[b + d]) return true;
			return false;
		};
		for (int i = 0; i < m; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) cnt[r[i + d]]++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) idx[--cnt[r[i + d]]] = i;
		for (int i = 0; i < m; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) cnt[r[i]]++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--cnt[r[idx[i]]]] = idx[i];
		nr[sa[0]] = 1;
		for (int i = 1; i < n; i++) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		for (int i = 0; i < n; i++) r[i] = nr[i];
		if (r[sa[n - 1]] == n) break;
	}
	return sa;
};

auto get_lcp = [](string s, auto sa) {
	int n = s.size();
	vector lcp(n - 1, 0), isa(n, 0);
	for (int i = 0; i < n; i++) isa[sa[i]] = i;
	for (int i = 0, k = 0; i < n; i++) if (isa[i]) {
		for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
		lcp[isa[i] - 1] = k ? k-- : 0;
	}
	return lcp;
};

auto sol = [](string s) {
	if (s.size() == 1) return true;
	auto sa = get_sa(s);
	auto lcp = get_lcp(s, sa);
	vector buc(s.size(), vector(0, 0));
	segtree tree(s.size() - 1);
	for (int i = 0; i < s.size() - 1; i++) {
		buc[lcp[i]].push_back(i);
		tree.update(i, lcp[i]);
	}
	auto rec = [&](const auto& self, int l, int r, int x) -> bool {
		if (l == r) return false;
		auto it = lower_bound(buc[x].begin(), buc[x].end(), l);
		vector cand(1, l - 1);
		while (it != buc[x].end() && *it < r) cand.push_back(*it++);
		cand.push_back(r);
		for (int i = 1; i < cand.size(); i++) {
			int a = cand[i - 1] + 1;
			int b = cand[i];
			int val = min((int)s.size() - sa[a], tree.query(a, b - 1));
			bool res = self(self, a, b, val);
			if ((val - x) % 2 == 0) res = !res;
			if (!res) return true;
		}
		return false;
	};
	return rec(rec, 0, s.size() - 1, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string s; cin >> s;
		cout << (sol(s) ? "Alice" : "Bob") << '\n';
	}
}