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
	vector p(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		p[i] = pow(i, mod - 2);
		p[i] = add(p[i], p[i - 1]);
	}
	int ret = 0, acc = 0;
	for (int i = 1; i <= (n + 1) / 2; i++) {
		acc = add(acc, sub(p[n - i + 1], p[i - 1]));
		ret = add(ret, mul(v[i - 1], acc));
		if (i - 1 != n - i) ret = add(ret, mul(v[n - i], acc));
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