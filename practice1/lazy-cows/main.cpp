#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector c(0, 0);
	for (int i = 0; i < n; i++) c.push_back(v[i][1]);
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector d(c.size(), 0);
	for (int i = 0; i < n; i++) {
		int j = lower_bound(c.begin(), c.end(), v[i][1]) - c.begin();
		if (v[i][0] == 1) d[j] |= 1;
		if (v[i][0] == 2) d[j] |= 2;
	}
	vector dp(c.size(), vector(m + 1, array{ -1, -1, -1, -1 }));
	auto rec = [&](const auto& self, int i, int j, int s) -> int {
		if (i == c.size()) return 0;
		int& ret = dp[i][j][s - 1];
		if (ret != -1) return ret;
		ret = 1 << 30;
		if (j > 0 && d[i] == 1) ret = min(ret, self(self, i + 1, j - 1, 1) + 1);
		if (j > 0 && d[i] == 2) ret = min(ret, self(self, i + 1, j - 1, 2) + 1);
		if (j > 0) ret = min(ret, self(self, i + 1, j - 1, 3) + 2);
		if (j > 1) ret = min(ret, self(self, i + 1, j - 2, 4) + 2);
		if (i == 0) return ret;
		if (s == 1) { // up
			if (d[i] == 1) ret = min(ret, self(self, i + 1, j, 1) + (c[i] - c[i - 1]));
			if (j > 0) ret = min(ret, self(self, i + 1, j - 1, 4) + (c[i] - c[i - 1]) + 1);
		}
		else if (s == 2) { // down
			if (d[i] == 2) ret = min(ret, self(self, i + 1, j, 2) + (c[i] - c[i - 1]));
			if (j > 0) ret = min(ret, self(self, i + 1, j - 1, 4) + (c[i] - c[i - 1]) + 1);
		}
		else if (s == 3) { // both
			ret = min(ret, self(self, i + 1, j, 3) + 2 * (c[i] - c[i - 1]));
		}
		else { // sep
			ret = min(ret, self(self, i + 1, j, 4) + 2 * (c[i] - c[i - 1]));
			if (d[i] == 1) ret = min(ret, self(self, i + 1, j, 1) + (c[i] - c[i - 1]));
			if (d[i] == 2) ret = min(ret, self(self, i + 1, j, 2) + (c[i] - c[i - 1]));
		}
		return ret;
	};
	return rec(rec, 0, m, 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, v) << '\n';
}