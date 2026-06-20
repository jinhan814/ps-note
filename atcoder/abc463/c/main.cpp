#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector dp(n, 0);
	for (int i = n - 1; i >= 0; i--) {
		if (i + 1 < n) dp[i] = dp[i + 1];
		dp[i] = max(dp[i], v[i][0]);
	}
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		int lo = -1, hi = n - 1;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (v[mid][1] <= qs[i]) lo = mid;
			else hi = mid;
		}
		ret[i] = dp[hi];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	int q; cin >> q;
	vector qs(q, 0);
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}