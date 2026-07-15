#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

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

auto sol = [](int n, i64 m, auto v) {
	i64 ret = 0;
	for (int mask = 0; mask < 1 << n; mask++) {
		i64 x = m;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			x -= v[i] + 1;
		}
		if (x < 0) continue;
		int a = 1, b = 1;
		for (int i = 1; i <= n - 1; i++) {
			a = mul(a, (x + i) % mod);
			b = mul(b, i);
		}
		int val = mul(a, pow(b, mod - 2));
		if (__builtin_popcount(mask) & 1) ret = sub(ret, val);
		else ret = add(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 m; cin >> m;
	vector v(n, i64(0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}