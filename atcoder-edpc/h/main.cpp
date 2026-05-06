#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto v) {
	vector dp(n, 0);
	for (int i = 0; i < m; i++) {
		if (v[0][i] == '#') break;
		dp[i] = 1;
	}
	for (int i = 1; i < n; i++) {
		vector ndp(n, 0);
		for (int j = 0; j < m; j++) {
			if (v[i][j] == '#') continue;
			ndp[j] = dp[j];
			if (j > 0) ndp[j] = add(ndp[j], ndp[j - 1]);
		}
		dp.swap(ndp);
	}
	return dp[m - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}