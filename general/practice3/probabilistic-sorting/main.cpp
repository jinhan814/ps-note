#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
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
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector dp(n + 1, fenwick(n));
	for (int x : v) {
		dp[1].update(x, 1);
		for (int i = 2; i <= n; i++) {
			int val = dp[i - 1].query(x - 1);
			dp[i].update(x, val);
		}
	}
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int v1 = dp[i].query(n);
		int v2 = bino(n, i);
		ret = add(ret, mul(v1, pow(v2, mod - 2)));
	}
	ret = sub(n, ret);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}