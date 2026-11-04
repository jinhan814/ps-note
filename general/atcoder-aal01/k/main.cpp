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
	int query(int l, int r) const {
		if (l > r) return 0;
		return sub(query(r), query(l - 1));
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	auto c = v;
	for (auto [op, x] : qs) if (op != 3) c.push_back(x);
	sort(v.begin(), v.end());
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	int acc = 0;
	fenwick t1(c.size()), t2(c.size());
	for (int i = 0, p = 0; i < n; i++) {
		while (v[i] != c[p]) p++;
		v[i] %= mod;
		acc = add(acc, mul(i + 1, v[i]));
		t1.update(p + 1, 1);
		t2.update(p + 1, v[i]);
	}
	auto push = [&](int x) {
		int p = lower_bound(c.begin(), c.end(), x) - c.begin();
		x %= mod;
		t1.update(p + 1, 1);
		t2.update(p + 1, x);
		acc = add(acc, mul(t1.query(p + 1), x));
		acc = add(acc, t2.query(p + 2, c.size()));
	};
	auto pop = [&](int x) {
		int p = lower_bound(c.begin(), c.end(), x) - c.begin();
		x %= mod;
		acc = sub(acc, mul(t1.query(p + 1), x));
		acc = sub(acc, t2.query(p + 2, c.size()));
		t1.update(p + 1, sub(0, 1));
		t2.update(p + 1, sub(0, x));
	};
	vector ret(0, 0);
	for (auto [op, x] : qs) {
		if (op == 1) push(x);
		else if (op == 2) pop(x);
		else ret.push_back(acc);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, pair(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [op, x] : qs) {
		cin >> op;
		if (op != 3) cin >> x;
	}
	auto res = sol(n, q, v, qs);
	for (int x : res) cout << x << '\n';
}