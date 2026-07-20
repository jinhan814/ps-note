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
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	vector c(n, false);
	fenwick tree(n);
	int p = 0;
	for (int i = n - 1; i >= 0; i--) {
		v[i] %= n;
		if (c[v[i]]) return 0;
		if (tree.query(v[i]) % 2) p ^= 1;
		tree.update(v[i] + 1, 1);
		c[v[i]] = true;
	}
	int ret = 1, acc = 1;
	for (int i = 1; i <= n - 1; i++) {
		acc = i64(acc) * i % n;
		ret = i64(ret) * acc % n;
	}
	if (p) ret = (n - ret) % n;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}