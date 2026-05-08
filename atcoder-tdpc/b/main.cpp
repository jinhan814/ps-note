#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector dp(n + 1, vector(m + 1, 1 << 30));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == n && j == m) return 0;
		int& ret = dp[i][j];
		if (ret != 1 << 30) return ret;
		ret = -(1 << 30);
		if (i < n) ret = max(ret, a[i] - self(self, i + 1, j));
		if (j < m) ret = max(ret, b[j] - self(self, i, j + 1));
		return ret;
	};
	int res = rec(rec, 0, 0);
	int acc = 0;
	for (int x : a) acc += x;
	for (int x : b) acc += x;
	return (res + acc) / 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}