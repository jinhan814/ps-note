#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m) {
	vector dp(n + 2, vector(n + 2, vector(m + 1, -1)));
	auto rec = [&](const auto& self, int x, int y, int rem) {
		if (rem < 0) return 0;
		if (x == 1 && y == n + 1) return rem == 0 ? 1 : 0;
		int& ret = dp[x][y][rem];
		if (ret != -1) return ret;
		ret = 0;
		if (x - 1 >= 1) ret = add(ret, self(self, x - 1, y, rem - (n - x - y + 3)));
		if (y + 1 <= n + 1 && x + y <= n + 2) ret = add(ret, self(self, x, y + 1, rem));
		return ret;
	};
	return rec(rec, n + 1, 1, m);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}