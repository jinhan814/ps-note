#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector c(1 << n, i64(0));
	for (int mask = 1; mask < 1 << n; mask++) {
		int p = 0;
		while (~mask >> p & 1) p++;
		c[mask] = c[mask ^ 1 << p];
		for (int i = p + 1; i < n; i++) {
			if (~mask >> i & 1) continue;
			c[mask] += v[i][p];
		}
	}
	vector dp(1 << n, i64(-1));
	auto rec = [&](const auto& self, int mask) -> i64 {
		if (mask == 0) return 0;
		i64& ret = dp[mask];
		if (ret != -1) return ret;
		ret = -(i64(1) << 60);
		for (int s = mask; s > 0; s = (s - 1) & mask) {
			i64 v1 = self(self, mask ^ s);
			i64 v2 = c[s];
			ret = max(ret, v1 + v2);
		}
		return ret;
	};
	return rec(rec, (1 << n) - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	cout << sol(n, v) << '\n';
}