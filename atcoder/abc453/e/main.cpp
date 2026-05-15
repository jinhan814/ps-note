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
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector buc(n + 1, vector(0, 0));
	vector psum(n + 1, 0);
	for (int i = 0; i < n; i++) {
		auto [a, b] = v[i];
		buc[a].push_back(b);
		psum[b]++;
		psum[a - 1]--;
	}
	for (int i = n; i >= 1; i--) {
		psum[i - 1] += psum[i];
	}
	fenwick tree(n);
	vector c(n + 1, 0);
	for (int i = 1; i <= n / 2; i++) {
		for (int x : buc[i]) tree.update(x, 1);
		c[i] = tree.query(n - i, n);
	}
	int ret = 0;
	for (int x = 1; x <= n - 1; x++) {
		int v1 = psum[x];
		int v2 = psum[n - x];
		int v3 = c[min(x, n - x)];
		if (v1 + v2 - v3 != n) continue;
		if (v1 - v3 > x) continue;
		if (v2 - v3 > n - x) continue;
		ret = add(ret, bino(v3, v1 - x));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}