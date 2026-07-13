#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	vector dp(2 * k + 1, i64(0));
	for (auto [a, b] : v) {
		vector ndp(2 * k + 1, i64(0));
		for (int i = 0; i <= 2 * k; i++) {
			if (i % 2 == 0) {
				ndp[i] = dp[i] + a;
				if (i > 0) ndp[i] = max(ndp[i], dp[i - 1] + a);
			}
			else {
				ndp[i] = dp[i] + b;
				if (i > 0) ndp[i] = max(ndp[i], dp[i - 1] + b);
			}
		}
		dp.swap(ndp);
	}
	return *max_element(dp.begin(), dp.end());
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, k, v) << '\n';
}