#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 10'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] = add(tree[i], x);
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret = add(ret, tree[i]);
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto v) {
	bool flag = true;
	for (int i = 1; i < n; i++) {
		if (v[i - 1] >= v[i]) continue;
		flag = false;
		break;
	}
	if (flag) return 1;
	auto c = v;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	for (int i = 0; i <= n - 1; i++) {
		auto it = lower_bound(c.begin(), c.end(), v[i]);
		v[i] = it - c.begin() + 1;
	}
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector tree(n + 1, fenwick(c.size()));
	for (int i = n - 1; i >= 0; i--) {
		for (int x = n - i; x >= 2; x--) {
			int val = tree[x - 1].query(v[i]);
			tree[x].update(v[i], val);
		}
		tree[1].update(v[i], 1);
	}
	int ret = 0;
	for (int k = 1; k <= n - 1; k++) {
		int v1 = mul(n - k, tree[k].query(c.size()));
		int v2 = mul(k + 1, tree[k + 1].query(c.size()));
		ret = add(ret, mul(sub(v1, v2), fac[n - k - 1]));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << iter << ": ";
		cout << sol(n, v) << '\n';
	}
}