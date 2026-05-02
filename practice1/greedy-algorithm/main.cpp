#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, int m, auto v) {
	vector cnt(n, vector(1'001, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int val = v[i][j];
			if (i > 0) val -= v[i - 1][j];
			else val -= v[n - 1][j];
			cnt[i][val + 500]++;
		}
	}
	vector dp(1'000 * n + 1, -1);
	dp[500 * n] = 0;
	for (int iter = 0; iter < n; iter++) {
		auto ndp = dp;
		for (int x = -500; x <= 500; x++) {
			int val = cnt[iter][x + 500];
			if (val == 0) continue;
			for (int i = 0; i <= 1'000 * n; i++) {
				if (dp[i] == -1) continue;
				int j = i + x;
				if (j < 0 || j > 1'000 * n) continue;
				ndp[j] = max(ndp[j], dp[i] + val);
			}
		}
		dp.swap(ndp);
	}
	int ret = 0, mn = 1 << 30;
	for (int iter = 0; iter < n; iter++) {
		int mx = *max_element(cnt[iter].begin(), cnt[iter].end());
		ret += mx;
		mn = min(mn, mx);
	}
	ret -= mn;
	ret = max(ret, dp[500 * n]);
	return ret;
};

auto sol = [](int n, int m, auto v) {
	vector nv(m, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) nv[j][i] = v[i][j];
	}
	return calc(n, m, v) + calc(m, n, nv);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, v) << '\n';
}