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

auto sol = [](int n, i64 l, i64 r, auto v) {
	for (int i = 1; i <= n; i++) v[i] += v[i - 1];
	auto c = v;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	i64 ret = 0;
	fenwick tree(c.size());
	for (int i = 0; i <= n; i++) {
		int pl = lower_bound(c.begin(), c.end(), v[i] - r) - c.begin();
		int pr = upper_bound(c.begin(), c.end(), v[i] - l) - c.begin();
		ret += tree.query(pr) - tree.query(pl);
		tree.update(lower_bound(c.begin(), c.end(), v[i]) - c.begin() + 1, 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 l, r; cin >> l >> r;
	vector v(n + 1, i64(0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, l, r, v) << '\n';
}