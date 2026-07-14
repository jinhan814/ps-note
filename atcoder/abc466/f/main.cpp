#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 m, auto v) {
	vector c(0, i64(0));
	for (i64 x : v) {
		if (c.size() && c.back() <= x) continue;
		c.push_back(x);
	}
	vector dp(c.size(), i64(-1));
	auto rec = [&](const auto& self, int i, i64 m) {
		if (i == c.size() - 1) return m / c.back();
		if (i > 0 && m == c[i - 1] - 1 && dp[i] != -1) return dp[i];
		i64 ret = 0;
		if (m >= c[i]) {
			i64 v1 = m / c[i];
			i64 v2 = self(self, i + 1, c[i] - 1);
			ret += v1 * (v2 + 1);
		}
		if (m % c[i] > 0) {
			int lo = i, hi = c.size() - 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				if (c[mid] > m % c[i]) lo = mid;
				else hi = mid;
			}
			ret += self(self, hi, m % c[i]);
		}
		if (i > 0 && m == c[i - 1] - 1) dp[i] = ret;
		return ret;
	};
	return rec(rec, 0, m);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		i64 m; cin >> m;
		vector v(n, i64(0));
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, m, v) << '\n';
	}
}