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
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto v) {
	i64 ret = i64(n) * (n + 1) / 2;
	fenwick tree(n);
	for (int i = 1; i <= n; i++) {
		int x = tree.query(v[i] - 1);
		ret += i64(x) * (v[i] - 1 - x);
		tree.update(v[i], 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}