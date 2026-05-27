#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto modadd = [](int a, int b, int mod) {
	return a + b < mod ? a + b : a + b - mod;
};

auto modmul = [](int a, int b, int mod) {
	return i64(a) * b % mod;
};

auto modpow = [](int x, i64 n, int mod) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = modmul(ret, x, mod);
		x = modmul(x, x, mod);
	}
	return ret;
};

auto sol = [](int n, int m, auto a, auto b) {
	int mod = 10'007 * m;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int v1 = modpow(10, b[i], 9 * mod);
		int v2 = modmul(a[i], modadd(v1, 9 * mod - 1, 9 * mod), 9 * mod);
		ret = modmul(ret, v1 % mod, mod);
		ret = modadd(ret, v2 / 9, mod);
	}
	ret = ret / m % 10'007;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, m, a, b) << '\n';
}