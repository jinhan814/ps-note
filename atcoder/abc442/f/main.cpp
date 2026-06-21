#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector p(n, vector(n + 1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			p[i][j + 1] = p[i][j];
			if (v[i][j] == '#') p[i][j + 1]++;
		}
	}
	vector dp(n, vector(n + 1, -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == n) return 0;
		int& ret = dp[i][j];
		if (ret != -1) return ret;
		ret = self(self, i + 1, j);
		ret += p[i][j];
		ret += (n - j) - (p[i][n] - p[i][j]);
		if (j > 0) {
			int val = self(self, i, j - 1);
			if (v[i][j - 1] == '#') val++;
			else val--;
			ret = min(ret, val);
		}
		return ret;
	};
	int ret = 1 << 30;
	for (int i = 0; i <= n; i++) {
		int val = rec(rec, 0, i);
		ret = min(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}