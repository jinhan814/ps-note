#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto matmul = [](auto a, auto b) {
	int n = a.size();
	vector ret(n, vector(n, i64(1) << 60));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				i64 val = a[i][k] + b[k][j];
				ret[i][j] = min(ret[i][j], val);
			}
		}
	}
	return ret;
};

auto matpow = [](auto v, int k) {
	int n = v.size();
	vector ret(n, vector(n, i64(1) << 60));
	for (int i = 0; i < n; i++) ret[i][i] = 0;
	for (; k; k >>= 1) {
		if (k & 1) ret = matmul(ret, v);
		v = matmul(v, v);
	}
	return ret;
};

auto sol = [](int n, int k, auto v) {
	v = matpow(v, k);
	vector ret(n, i64(0));
	for (int i = 0; i < n; i++) ret[i] = v[i][i];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, vector(n, i64(0)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	auto res = sol(n, k, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}