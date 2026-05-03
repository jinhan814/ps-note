#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector dp(n, vector(m, vector(32, -1)));
	auto rec = [&](const auto& self, int x, int y, int f1, int f2, int f3, int f4, int f5) -> int {
		if (x == n - 1 && y == m - 1) return v[x][y] != '.' && !f4 ? v[x][y] - '0' : 0;
		int& ret = dp[x][y][f1 | f2 << 1 | f3 << 2 | f4 << 3 | f5 << 4];
		if (ret != -1) return ret;
		ret = 0;
		int mask = 0;
		if (v[x][y] != '.' && !f4) {
			mask |= 1;
			ret += v[x][y] - '0';
		}
		if (x - 1 >= 0 && v[x - 1][y] != '.' && !f1) {
			mask |= 2;
			ret += v[x - 1][y] - '0';
		}
		if (y - 1 >= 0 && v[x][y - 1] != '.' && !f3) {
			mask |= 4;
			ret += v[x][y - 1] - '0';
		}
		if (x + 1 < n && v[x + 1][y] != '.') {
			mask |= 8;
			ret += v[x + 1][y] - '0';
		}
		if (y + 1 < m && v[x][y + 1] != '.') {
			mask |= 16;
			ret += v[x][y + 1] - '0';
		}
		int mn = 1 << 30;
		if (x + 1 < n) {
			int nf1 = f4 || mask & 1;
			int nf2 = mask >> 4 & 1;
			int nf3 = f5;
			int nf4 = mask >> 3 & 1;
			int nf5 = 0;
			mn = min(mn, self(self, x + 1, y, nf1, nf2, nf3, nf4, nf5));
		}
		if (y + 1 < m) {
			int nf1 = f2;
			int nf2 = 0;
			int nf3 = f4 || mask & 1;
			int nf4 = mask >> 4 & 1;
			int nf5 = mask >> 3 & 1;
			mn = min(mn, self(self, x, y + 1, nf1, nf2, nf3, nf4, nf5));
		}
		if (mask & 2) {
			if (x + 1 < n) {
				int nf1 = f4 || mask & 1;
				int nf2 = mask >> 4 & 1;
				int nf3 = f5;
				int nf4 = mask >> 3 & 1;
				int nf5 = 0;
				mn = min(mn, self(self, x + 1, y, nf1, nf2, nf3, nf4, nf5) - (v[x - 1][y] - '0'));
			}
			if (y + 1 < m) {
				int nf1 = f2;
				int nf2 = 0;
				int nf3 = f4 || mask & 1;
				int nf4 = mask >> 4 & 1;
				int nf5 = mask >> 3 & 1;
				mn = min(mn, self(self, x, y + 1, nf1, nf2, nf3, nf4, nf5) - (v[x - 1][y] - '0'));
			}
		}
		if (mask & 4) {
			if (x + 1 < n) {
				int nf1 = f4 || mask & 1;
				int nf2 = mask >> 4 & 1;
				int nf3 = f5;
				int nf4 = mask >> 3 & 1;
				int nf5 = 0;
				mn = min(mn, self(self, x + 1, y, nf1, nf2, nf3, nf4, nf5) - (v[x][y - 1] - '0'));
			}
			if (y + 1 < m) {
				int nf1 = f2;
				int nf2 = 0;
				int nf3 = f4 || mask & 1;
				int nf4 = mask >> 4 & 1;
				int nf5 = mask >> 3 & 1;
				mn = min(mn, self(self, x, y + 1, nf1, nf2, nf3, nf4, nf5) - (v[x][y - 1] - '0'));
			}
		}
		if (mask & 8) {
			if (x + 1 < n) {
				int nf1 = f4 || mask & 1;
				int nf2 = mask >> 4 & 1;
				int nf3 = f5;
				int nf4 = 0;
				int nf5 = 0;
				mn = min(mn, self(self, x + 1, y, nf1, nf2, nf3, nf4, nf5) - (v[x + 1][y] - '0'));
			}
			if (y + 1 < m) {
				int nf1 = f2;
				int nf2 = 0;
				int nf3 = f4 || mask & 1;
				int nf4 = mask >> 4 & 1;
				int nf5 = 0;
				mn = min(mn, self(self, x, y + 1, nf1, nf2, nf3, nf4, nf5) - (v[x + 1][y] - '0'));
			}
		}
		if (mask & 16) {
			if (x + 1 < n) {
				int nf1 = f4 || mask & 1;
				int nf2 = 0;
				int nf3 = f5;
				int nf4 = mask >> 3 & 1;
				int nf5 = 0;
				mn = min(mn, self(self, x + 1, y, nf1, nf2, nf3, nf4, nf5) - (v[x][y + 1] - '0'));
			}
			if (y + 1 < m) {
				int nf1 = f2;
				int nf2 = 0;
				int nf3 = f4 || mask & 1;
				int nf4 = 0;
				int nf5 = mask >> 3 & 1;
				mn = min(mn, self(self, x, y + 1, nf1, nf2, nf3, nf4, nf5) - (v[x][y + 1] - '0'));
			}
		}
		ret += mn;
		return ret;
	};
	return rec(rec, 0, 0, 0, 0, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}