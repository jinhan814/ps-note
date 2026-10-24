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
	vector c(n, 0);
	for (int i = 0; i < n; i++) c[i] = v[i][1];
	sort(v.begin(), v.end());
	sort(c.begin(), c.end());
	i64 ret = 0;
	for (int i = 0; i < n; i++) {
		int p = lower_bound(c.begin(), c.end(), v[i][1]) - c.begin();
		ret += abs((v[i][0] - i) - (v[i][1] - p));
	}
	fenwick tree(n);
	for (int i = n - 1; i >= 0; i--) {
		int p = lower_bound(c.begin(), c.end(), v[i][1]) - c.begin() + 1;
		ret += tree.query(p);
		tree.update(p, 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0];
	for (int i = 0; i < n; i++) cin >> v[i][1];
	cout << sol(n, v) << '\n';
}