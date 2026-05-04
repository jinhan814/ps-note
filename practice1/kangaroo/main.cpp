#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, auto a, auto b) {
	sort(a.begin(), a.end(), greater{});
	sort(b.begin(), b.end(), greater{});
	vector f(n, 0);
	for (int i = 0; i < n; i++) {
		if (i > 0) f[i] = f[i - 1];
		while (f[i] < n && b[f[i]] > a[i]) f[i]++;
	}
	vector dp(n + 1, vector(n + 1, 0));
	for (int i = 0; i <= n; i++) dp[i][0] = 1;
	for (int i = n - 1; i >= 0; i--) {
		vector ndp(n + 1, vector(n + 1, 0));
		for (int x = 0; x <= f[i]; x++) {
			for (int y = 0; y <= f[i]; y++) {
				ndp[x][y] = dp[x][f[i] - x];
				if (y > 0) {
					int val = dp[x + 1][y - 1];
					val = mul(val, y);
					ndp[x][y] = add(ndp[x][y], val);
				}
				if (f[i] - x - y > 0) {
					int val = dp[x + 1][y];
					val = mul(val, f[i] - x - y);
					ndp[x][y] = add(ndp[x][y], val);
				}
			}
		}
		dp.swap(ndp);
	}
	return dp[0][0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, a, b) << '\n';
}