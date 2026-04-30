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

auto sol = [](int n, int m) {
	vector dp(n + 1, vector(m + 1, -1));
	auto rec = [&](const auto& self, int n, int m) -> int {
		if (n <= 0 || m <= 0) return 1;
		int& ret = dp[n][m];
		if (ret != -1) return ret;
		ret = self(self, n - 1, m);
		ret = add(ret, mul(4 * m, self(self, n - 1, m - 1)));
		ret = add(ret, mul(m * (m - 1) / 2, self(self, n - 1, m - 2)));
		ret = add(ret, mul(m * (n - 1), self(self, n - 2, m - 1)));
		return ret;
	};
	return sub(rec(rec, n, m), 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}