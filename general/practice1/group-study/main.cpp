#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return 1LL * a * b % mod;
}

auto sol = [](int n) {
	vector dp(1, vector(51, 0));
	for (int k = 0; k <= 50; k++) dp[0][k] = 1;
	for (int i = n - 1; i >= 0; i--) {
		vector ndp(n - i + 1, vector(51, 0));
		for (int j = 0; j <= n - i; j++) {
			for (int k = 0; k <= 50; k++) {
				if (n - i - j >= 1) {
					int val = mul(dp[j][k], n - i - j);
					ndp[j][k] = add(ndp[j][k], val);
				}
				if (j >= i + 1) {
					int val = mul(dp[j - i - 1][k + 1], mul(i + 1, k + 1));
					ndp[j][k] = add(ndp[j][k], val);
				}
			}
		}
		dp.swap(ndp);
	}
	return dp[n][0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	cout << sol(n) << '\n';
}