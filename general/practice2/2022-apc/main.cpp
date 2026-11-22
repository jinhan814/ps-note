#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
};

auto sol = [](int n, int m, auto v) {
	vector dp(3'001, 0);
	for (int i = v[0][0]; i <= v[0][1]; i++) dp[i] = 1;
	for (int iter = 1; iter < n; iter++) {
		vector ndp(3'001, 0);
		for (int i = 1; i <= 3'000; i++) {
			int l = max(i - m, v[iter][0]);
			int r = min(i + m, v[iter][1]);
			if (l > r) continue;
			ndp[r] = add(ndp[r], dp[i]);
			ndp[l - 1] = sub(ndp[l - 1], dp[i]);
		}
		for (int i = 2'999; i >= 0; i--) {
			ndp[i] = add(ndp[i], ndp[i + 1]);
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int i = 1; i <= 3'000; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, v) << '\n';
}