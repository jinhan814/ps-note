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

auto sol = [](int n, int m, auto a, auto b) {
	int v1 = 0, v2 = 0;
	for (int i = 1; i <= n; i++) {
		v1 = add(v1, mul(i, a[i]));
	}
	for (int i = 1; i <= m; i++) {
		v2 = add(v2, b[i]);
	}
	vector psum(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		psum[i] = add(psum[i - 1], a[i]);
	}
	int ret = mul(v1, v2);
	for (int j = 1; j <= m; j++) {
		for (int k = 1; j * k <= n; k++) {
			int l = j * k;
			int r = j * k + j - 1;
			if (r > n) r = n;
			int val = sub(psum[r], psum[l - 1]);
			val = mul(val, b[j]);
			val = mul(val, j * k);
			ret = sub(ret, val);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n + 1, 0), b(m + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}