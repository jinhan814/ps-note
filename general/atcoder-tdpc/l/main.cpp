#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(n + 1, 0);
	for (int p = n - 1; p >= 0; p--) {
		vector ndp(p + 1, 0);
		int acc = 0;
		for (int i = p; i >= 0; i--) {
			acc += v[i][p];
			ndp[i] = acc + dp[i];
			if (i != p) ndp[i] = min(ndp[i], ndp[i + 1] + v[i][p]);
			else ndp[i] = min(ndp[i], dp[i + 1]);
		}
		dp.swap(ndp);
	}
	return dp[0] * 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	cout << sol(n, v) << '\n';
}