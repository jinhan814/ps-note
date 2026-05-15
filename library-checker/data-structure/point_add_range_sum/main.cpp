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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	fenwick tree(n);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		tree.update(i, x);
	}
	while (q--) {
		int op, a, b; cin >> op >> a >> b;
		if (op == 0) tree.update(a + 1, b);
		else cout << tree.query(a + 1, b) << '\n';
	}
}