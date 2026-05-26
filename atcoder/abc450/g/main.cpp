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
	int v1 = 0, v2 = 0, acc = 0;
	for (int i = 0; i < n; i++) {
		v1 = add(v1, mul(v[i], v[i]));
		v2 = add(v2, mul(acc, v[i]));
		acc = add(acc, v[i]);
	}
	if (n == 1) return v1;
	if (n == 2) return sub(v1, mul(2, v2));
	v2 = mul(v2, 4);
	v2 = mul(v2, pow(3 * (n - 1), mod - 2));
	return sub(v1, v2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}