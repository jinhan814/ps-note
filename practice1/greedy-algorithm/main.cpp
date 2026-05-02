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
	vector dp(1, 0);
	for (int iter = 1; iter < n; iter++) {
		vector ndp(1'000 * iter + 1, *max_element(dp.begin(), dp.end()));
		vector cand(0, 0);
		for (int x = -500; x <= 500; x++) {
			if (cnt[iter][-x + 500] == 0) continue;
			cand.push_back(x);
		}
		for (int i = -500 * (iter - 1); i <= 500 * (iter - 1); i++) {
			for (int x : cand) {
				int p = i + x + 500 * iter;
				ndp[p] = max(ndp[p], dp[i + 500 * (iter - 1)] + cnt[iter][-x + 500]);
			}
		}
		dp.swap(ndp);
	}
	int ret = 0, mn = 1 << 30;
	for (int i = 0; i < n; i++) {
		int mx = -1;
		for (int x = -500; x <= 500; x++) mx = max(mx, cnt[i][x + 500]);
		ret += mx;
		mn = min(mn, mx);
	}
	ret -= mn;
	for (int i = -500 * (n - 1); i <= 500 * (n - 1); i++) {
		int val = dp[i + 500 * (n - 1)];
		if (abs(i) <= 500) val += cnt[0][i + 500];
		ret = max(ret, val);
	}
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