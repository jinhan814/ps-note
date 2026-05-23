#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector dp(n, 0), c(0, 0);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(c.begin(), c.end(), v[i]);
		dp[i] = it - c.begin() + 1;
		if (it == c.end()) c.push_back(v[i]);
		else *it = v[i];
	}
	int mx = *max_element(dp.begin(), dp.end());
	vector ret(mx, 0);
	for (int i = n - 1, j = mx; i >= 0; i--) {
		if (dp[i] != j) continue;
		ret[--j] = i;
	}
	return pair(mx, ret);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto [mx, res] = sol(n, v);
	cout << mx << '\n';
	for (int i = 0; i < mx; i++) cout << res[i] << ' ';
	cout << '\n';
}