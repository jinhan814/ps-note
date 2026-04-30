#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 20'070'713;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) { return a[1] < b[1]; });
	vector dp(n + 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		int lo = 0, hi = i;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (v[mid][1] < v[i][0]) lo = mid;
			else hi = mid;
		}
		dp[i] = add(dp[i - 1], dp[lo]);
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}