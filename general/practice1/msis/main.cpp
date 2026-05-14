#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	v.push_back(array{ 0, 0 });
	v.push_back(array{ 100'000, 100'000 });
	sort(v.begin(), v.end());
	vector psum(n + 2, 0);
	for (int i = 1; i <= n + 1; i++) {
		psum[i] = max(v[i][0], v[i][1]);
		psum[i] += psum[i - 1];
	}
	vector dp(n + 2, 0);
	for (int i = 1; i <= n + 1; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (v[j][1] > v[i][1]) continue;
			int v1 = v[i][0] + v[i][1];
			int v2 = psum[i - 1] - psum[j];
			dp[i] = max(dp[i], dp[j] + v1 + v2);
		}
	}
	return dp[n + 1] - 200'000;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0];
	for (int i = 0; i < n; i++) cin >> v[i][1];
	cout << sol(n, v) << '\n';
}