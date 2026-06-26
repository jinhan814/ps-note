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

auto sol = [](int n, int m) {
	vector fac(n + m, 1);
	for (int i = 1; i <= n + m - 1; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + m, pow(fac[n + m - 1], mod - 2));
	for (int i = n + m - 1; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	int v1 = mul(bino(n + m - 1, n - 1), pow(2, m));
	int v2 = mul(bino(n + m - 1, n), pow(2, m - 1));
	return add(v1, v2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}