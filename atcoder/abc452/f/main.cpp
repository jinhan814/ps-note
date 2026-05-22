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
	int query(int l, int r) const {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

auto calc = [](int n, i64 k, auto v) {
	if (k < 0) return i64(0);
	i64 ret = 0, acc = 0;
	fenwick tree(n);
	for (int i = 1, j = 1; i <= n; i++) {
		while (j <= n) {
			i64 nacc = acc + tree.query(v[j] + 1, n);
			if (nacc > k) break;
			acc = nacc;
			tree.update(v[j], 1);
			j++;
		}
		ret += j - i;
		acc -= tree.query(1, v[i] - 1);
		tree.update(v[i], -1);
	}
	return ret;
};

auto sol = [](int n, i64 k, auto v) {
	return calc(n, k, v) - calc(n, k - 1, v);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}