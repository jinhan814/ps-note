#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(59, vector(n, -1));
	for (int x = 1; x <= 58; x++) {
		for (int i = 0; i < n; i++) {
			if (v[i] == x) dp[x][i] = i;
			int j = dp[x - 1][i];
			if (j == -1 || j + 1 >= n) continue;
			if (dp[x - 1][j + 1] == -1) continue;
			dp[x][i] = dp[x - 1][j + 1];
		}
	}
	for (int x = 58; x >= 1; x--) {
		for (int i = 0; i < n; i++) {
			if (dp[x][i] == -1) continue;
			return x;
		}
	}
	assert(0);
	return -1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}