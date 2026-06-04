#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto matmul = [](auto a, auto b) {
	int n = a.size();
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

auto matpow = [](auto v, int k) {
	int n = v.size();
	vector ret(n, vector(n, 0));
	for (int i = 0; i < n; i++) ret[i][i] = 1;
	for (; k; k >>= 1) {
		if (k & 1) ret = matmul(ret, v);
		v = matmul(v, v);
	}
	return ret;
};

auto sol = [](int n, int m, auto v) {
	vector c(m, vector(m, 0));
	for (int i = 0; i < m; i++) {
		vector dp(1 << m, vector(m, -1));
		auto rec = [&](const auto& self, int mask, int cur) -> int {
			if (mask == 1 << i) return 1;
			int& ret = dp[mask][cur];
			if (ret != -1) return ret;
			ret = 0;
			for (int nxt = 0; nxt < m; nxt++) {
				if (v[cur][nxt] == 0) continue;
				if (~mask >> nxt & 1) continue;
				ret = add(ret, self(self, mask ^ 1 << cur, nxt));
			}
			return ret;
		};
		for (int mask = 1; mask < 1 << m; mask++) {
			for (int j = 0; j < m; j++) {
				if (~mask >> j & 1) continue;
				c[i][j] = add(c[i][j], rec(rec, mask, j));
			}
		}
	}
	return matpow(c, n)[0][0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, vector(m, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, v) << '\n';
}