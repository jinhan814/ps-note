#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void clear() {
		fill(tree.begin(), tree.end(), 0);
	}
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
	vector dp1(n, 0);
	fenwick tree(n);
	for (int i = 0; i < n; i++) {
		dp1[i] = tree.query(v[i] - 1);
		tree.update(v[i], 1);
	}
	vector dp2(n, 0);
	tree.clear();
	for (int i = n - 1; i >= 0; i--) {
		dp2[i] = tree.query(v[i] - 1);
		tree.update(v[i], 1);
	}
	vector p(n + 1, 1);
	for (int i = 1; i <= n; i++) p[i] = mul(p[i - 1], 2);
	vector inv(n + 1, pow(p[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], 2);
	int ret = 0, acc = 0;
	for (int i = n - 1; i >= 0; i--) {
		ret = add(ret, mul(dp1[i], dp2[i]));
		ret = add(ret, mul(mul(dp1[i], inv[i + 1]), acc));
		acc = add(acc, mul(dp2[i], p[i]));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}