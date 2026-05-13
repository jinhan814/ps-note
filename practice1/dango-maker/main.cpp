#include <bits/stdc++.h>
using namespace std;

auto calc = [](auto v) {
	array dp{ 0, 0, 0 };
	for (int x : v) {
		array ndp{ 0, 0, 0 };
		ndp[0] = max({ dp[0], dp[1], dp[2] });
		if (x & 1) ndp[1] = max(dp[0], dp[1]) + 1;
		if (x & 2) ndp[2] = max(dp[0], dp[2]) + 1;
		dp.swap(ndp);
	}
	return max({ dp[0], dp[1], dp[2] });
};

auto sol = [](int n, int m, auto v) {
	vector c(n + m - 1, vector(0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x = 0;
			if (v[i][j] == 'G') {
				bool f1 = i - 1 >= 0 && v[i - 1][j] == 'R';
				bool f2 = i + 1 < n && v[i + 1][j] == 'W';
				if (f1 && f2) x |= 1;
				bool f3 = j - 1 >= 0 && v[i][j - 1] == 'R';
				bool f4 = j + 1 < m && v[i][j + 1] == 'W';
				if (f3 && f4) x |= 2;
			}
			c[i + j].push_back(x);
		}
	}
	int ret = 0;
	for (int i = 0; i <= n + m - 2; i++) ret += calc(c[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}