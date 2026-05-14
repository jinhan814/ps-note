#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto matmul = [](int n, auto a, auto b) {
	vector ret(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				int val = mul(a[i][k], b[k][j]);
				ret[i][j] = add(ret[i][j], val);
			}
		}
	}
	return ret;
};

auto matpow = [](int n, i64 k, auto v) {
	vector ret(n, vector(n, 0));
	for (int i = 0; i < n; i++) ret[i][i] = 1;
	for (; k; k >>= 1) {
		if (k & 1) ret = matmul(n, ret, v);
		v = matmul(n, v, v);
	}
	return ret;
};

auto sol = [](int n, i64 k, auto v) {
	auto c = matpow(n, k, v);
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) ret = add(ret, c[i][j]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector v(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	cout << sol(n, k, v) << '\n';
}