#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, auto v) {
	vector c(n + 1, 0);
	for (int i = 0; i < 2 * n; i++) c[v[i]]++;
	int c0 = 0, c1 = 0;
	for (int i = 1; i <= n; i++) {
		if (c[i] == 0) c0++;
		if (c[i] == 1) c1++;
	}
	vector bino(c0 + 1, vector(c0 + 1, 0));
	for (int i = 0; i <= c0; i++) {
		bino[i][0] = 1;
		bino[i][i] = 1;
		for (int j = 1; j <= i - 1; j++) {
			bino[i][j] = add(bino[i - 1][j - 1], bino[i - 1][j]);
		}
	}
	vector fac(2 * n + 1, 1);
	vector pow(2 * n + 1, 1);
	for (int i = 1; i <= 2 * n; i++) {
		fac[i] = mul(fac[i - 1], i);
		pow[i] = mul(pow[i - 1], (mod + 1) / 2);
	}
	vector dp(2 * n, vector(c0 + 1, vector(c1 + 1, -1)));
	auto rec = [&](const auto& self, int i, int a, int b) -> int {
		if (i <= 0) return a == 0 && b == 0;
		int& ret = dp[i][a][b];
		if (ret != -1) return ret;
		ret = self(self, i - 1, a, b);
		if (v[i - 1] == 0 && v[i] == 0 && a > 0) {
			int res = self(self, i - 2, a - 1, b);
			ret = add(ret, res);
		}
		if (v[i - 1] != 0 && c[v[i - 1]] == 1 && v[i] == 0 && b > 0) {
			int res = self(self, i - 2, a, b - 1);
			ret = add(ret, res);
		}
		if (v[i - 1] == 0 && v[i] != 0 && c[v[i]] == 1 && b > 0) {
			int res = self(self, i - 2, a, b - 1);
			ret = add(ret, res);
		}
		return ret;
	};
	int ret = 0;
	for (int a = 0; a <= c0; a++) {
		for (int b = 0; b <= c1; b++) {
			int val = rec(rec, 2 * n - 1, a, b);
			val = mul(val, bino[c0][a]);
			val = mul(val, fac[a]);
			val = mul(val, fac[2 * (c0 - a) + (c1 - b)]);
			val = mul(val, pow[c0 - a]);
			if ((a + b) % 2 == 0) ret = add(ret, val);
			else ret = sub(ret, val);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(2 * n, 0);
		for (int i = 0; i < 2 * n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}