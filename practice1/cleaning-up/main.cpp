#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector dp(n + 1, 1 << 30); dp[0] = 0;
	vector prv(m + 1, -1);
	set s{ 0 };
	for (int i = 1; i <= n; i++) {
		if (prv[v[i]] != -1) s.erase(prv[v[i]]);
		prv[v[i]] = i;
		s.insert(i);
		auto it = prev(s.end());
		for (int iter = 1; iter * iter <= n; iter++) {
			if (it == s.begin()) break;
			int j = *--it;
			dp[i] = min(dp[i], dp[j] + iter * iter);
		}
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}