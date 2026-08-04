#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto v) {
	vector c(0, 0);
	for (int x : v) {
		if (c.empty() || c.back() < -x) c.push_back(-x);
		else *lower_bound(c.begin(), c.end(), -x) = -x;
	}
	if (c.size() >= 3) return 0;
	vector dp(n + 1, 0);
	dp[0] = 1;
	for (int l = 0, r = 0; l < n; l = r) {
		int mn = 1 << 30;
		int mx = -(1 << 30);
		while (r < n) {
			mn = min(mn, v[r]);
			mx = max(mx, v[r]);
			r++;
			if (mn == l + 1 && mx == r) break;
		}
		int cnt = 0;
		for (int i = l; i < r; i++) {
			if (mn > v[i]) continue;
			mn = v[i];
			cnt++;
		}
		vector ndp(n + 1, 0);
		for (int iter = 0; iter < 2; iter++) {
			for (int i = n - cnt; i >= 0; i--) {
				ndp[i + cnt] = add(ndp[i + cnt], dp[i]);
			}
			cnt = r - l - cnt;
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int i = n - m; i <= m; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}