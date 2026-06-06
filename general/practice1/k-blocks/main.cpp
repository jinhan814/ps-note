#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector dp(n + 1, 1 << 30);
	dp[0] = 0;
	for (int iter = 1; iter <= k; iter++) {
		vector ndp(n + 1, 1 << 30);
		vector s(1, iter - 1);
		vector c(1, 1 << 30);
		vector p(1, 1 << 30);
		v[iter - 1] = 1 << 30;
		for (int i = iter; i <= n; i++) {
			int val = dp[i - 1] + v[i];
			while (v[s.back()] <= v[i]) {
				val = min(val, c.back() - v[s.back()] + v[i]);
				s.pop_back();
				c.pop_back();
				p.pop_back();
			}
			s.push_back(i);
			c.push_back(val);
			p.push_back(min(p.back(), val));
			ndp[i] = p.back();
		}
		dp.swap(ndp);
	}
	return dp[n];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}