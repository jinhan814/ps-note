#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector dp(3, -(i64(1) << 60));
	dp[1] = 0;
	for (int x : v) {
		auto ndp = dp;
		ndp[0] = max(ndp[0], dp[1] - x);
		ndp[1] = max(ndp[1], dp[0] + x);
		ndp[1] = max(ndp[1], dp[2] - x);
		ndp[2] = max(ndp[2], dp[1] + x);
		dp.swap(ndp);
	}
	return dp[1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}