#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << (__lg(n - 1 | 1) + 1)), tree(sz << 1, -(1 << 30)) {}
	void update(int i, int x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		int ret = -(1 << 30);
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int m, int k, auto v) {
	vector dp(m + 1, 0);
	vector p1(m + 1, 0), p2(m + 1, 0);
	vector d1(m + 1, 0), d2(m + 1, 0);
	segtree t1(m), t2(m);
	for (int i = 1; i <= m; i++) {
		p1[i] = p1[i - 1] + v[n][i];
		if (i >= k) dp[i] = p1[i] - p1[i - k];
	}
	for (int iter = n - 1; iter >= 1; iter--) {
		for (int i = 1; i <= m; i++) {
			p1[i] = p1[i - 1] + v[iter][i];
			p2[i] = p2[i - 1] + v[iter + 1][i];
		}
		for (int i = k; i <= m; i++) {
			if (i > k) d1[i] = d1[i - 1];
			d1[i] = max(d1[i], dp[i]);
			t1.update(i, dp[i] - p2[i]);
			t2.update(i, dp[i] + p2[i - k]);
		}
		for (int i = m; i >= k; i--) {
			if (i < m) d2[i] = d2[i + 1];
			d2[i] = max(d2[i], dp[i]);
		}
		vector ndp(m + 1, 0);
		for (int i = k; i <= m; i++) {
			ndp[i] = max(ndp[i], t1.query(max(i - k + 1, k), i) + p2[i]);
			ndp[i] = max(ndp[i], t2.query(i, min(i + k - 1, m)) - p2[i - k]);
			if (i - k >= k) ndp[i] = max(ndp[i], d1[i - k] + p2[i] - p2[i - k]);
			if (i + k <= m) ndp[i] = max(ndp[i], d2[i + k] + p2[i] - p2[i - k]);
			ndp[i] += p1[i] - p1[i - k];
		}
		dp.swap(ndp);
	}
	return *max_element(dp.begin() + k, dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n + 1, vector(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, k, v) << '\n';
}