#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector dp(n, vector(m, map<int, int>{}));
	auto f = [&](int i, int j) {
		return v[i][j] == '+' ? 1 : -1;
	};
	auto rec = [&](const auto& self, int i, int j, int mask) -> int {
		if (j == m) i++, j = 0;
		if (i == n) return 0;
		if (dp[i][j].count(mask)) return dp[i][j][mask];
		int ret = -(1 << 30);
		int nmask = (mask << 1) & ((1 << m) - 1);
		if (v[i][j] == '#') {
			ret = self(self, i, j + 1, nmask);
		}
		else if (j > 0 && v[i][j - 1] != '#') {
			if (mask & 1) {
				ret = self(self, i, j + 1, nmask | 1);
			}
			else if (~mask >> (m - 1) & 1) {
				ret = self(self, i, j + 1, nmask) + f(i, j);
			}
		}
		else {
			ret = self(self, i, j + 1, nmask | 1);
			if (~mask >> (m - 1) & 1) {
				ret = max(ret, self(self, i, j + 1, nmask) + f(i, j));
			}
		}
		return dp[i][j][mask] = ret;
	};
	return rec(rec, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}