#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector cnt(k, array{ 0, 0 });
	for (int i = 0; i < n; i++) cnt[i % k][v[i] % 2]++;
	vector dp{ cnt[0][1], cnt[0][0] };
	for (int i = 1; i < k; i++) {
		vector ndp(2, 0);
		ndp[0] = min(dp[0] + cnt[i][1], dp[1] + cnt[i][0]);
		ndp[1] = min(dp[0] + cnt[i][0], dp[1] + cnt[i][1]);
		dp.swap(ndp);
	}
	return dp[0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}