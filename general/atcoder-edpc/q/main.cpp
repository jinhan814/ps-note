#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] = max(tree[i], x);
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret = max(ret, tree[i]);
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, auto a, auto b) {
	fenwick tree(n);
	for (int i = 0; i < n; i++) {
		i64 val = tree.query(a[i]) + b[i];
		tree.update(a[i], val);
	}
	return tree.query(n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}