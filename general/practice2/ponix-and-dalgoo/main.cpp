#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	auto dp1 = v, dp2 = v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int mx = 0;
			if (i - 1 >= 0) mx = max(mx, dp1[i - 1][j]);
			if (j - 1 >= 0) mx = max(mx, dp1[i][j - 1]);
			dp1[i][j] += mx;
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			int mx = 0;
			if (i + 1 < n) mx = max(mx, dp2[i + 1][j]);
			if (j + 1 < n) mx = max(mx, dp2[i][j + 1]);
			dp2[i][j] += mx;
		}
	}
	int ret = 1 << 30;
	for (int iter = m; iter <= 2 * n - m - 2; iter++) {
		vector c(0, 0);
		for (int i = 0; i < n; i++) {
			int j = iter - i;
			if (j < 0 || j >= n) continue;
			int val = dp1[i][j] + dp2[i][j] - v[i][j];
			c.push_back(val);
		}
		auto p = c;
		for (int i = 1; i < c.size(); i++) {
			p[i] = max(p[i], p[i - 1]);
		}
		for (int i = c.size() - 1, x = 0; i >= m - 1; i--) {
			if (i + 1 < c.size()) x = max(x, c[i + 1]);
			int mx = x;
			if (i - m >= 0) mx = max(mx, p[i - m]);
			ret = min(ret, mx);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	cout << sol(n, m, v) << '\n';
}