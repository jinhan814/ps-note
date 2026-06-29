#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, string s, auto a, auto b) {
	vector dp(2, i64(0));
	dp[0] = s[0] == 'S' ? 0 : -a[0];
	dp[1] = s[0] == 'R' ? 0 : -a[0];
	for (int i = 1; i < n; i++) {
		vector ndp(2, i64(0));
		ndp[0] = max(dp[0], dp[1] + b[i]) + (s[i] == 'S' ? 0 : -a[i]);
		ndp[1] = max(dp[0], dp[1]) + (s[i] == 'R' ? 0 : -a[i]);
		dp.swap(ndp);
	}
	return max(dp[0], dp[1]);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		string s; cin >> s;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 1; i < n; i++) cin >> b[i];
		cout << sol(n, s, a, b) << '\n';
	}
}