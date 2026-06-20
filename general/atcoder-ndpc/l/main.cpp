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

auto sol = [](int n, auto v) {
	vector buc(n + 1, vector(0, 0));
	vector mu(n + 1, 0); mu[1] = 1;
	vector inv(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			buc[j].push_back(i);
			if (i != j) mu[j] -= mu[i];
		}
		inv[i] = pow(i, mod - 2);
	}
	vector c(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int d : buc[i]) {
			int val = mul(d, inv[i]);
			if (mu[d] == 1) c[i] = add(c[i], val);
			if (mu[d] == -1) c[i] = sub(c[i], val);
		}
	}
	vector dp(n + 1, 0);
	vector acc(n + 1, 0);
	auto update = [&](int i, int x) {
		dp[i] = x;
		int val = mul(x, v[i]);
		for (int d : buc[v[i]]) acc[d] = add(acc[d], val);
	};
	update(1, 1);
	for (int i = 2; i <= n; i++) {
		int val = 0;
		for (int d : buc[v[i]]) val = add(val, mul(c[d], acc[d]));
		val = mul(val, v[i]);
		update(i, val);
	}
	return dp;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 2; i <= n; i++) cout << res[i] << '\n';
}