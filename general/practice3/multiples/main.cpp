#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector c(n, 0);
	for (auto [a, b] : v) c[b - 1] = max(c[b - 1], a);
	vector dp(n, vector(n, -1));
	auto rec = [&](const auto& self, int l, int r) {
		if (l > r) return 0;
		int& ret = dp[l][r];
		if (ret != -1) return ret;
		ret = -(1 << 30);
		for (int i = l; i <= r - 1; i++) {
			int v1 = self(self, l, i);
			int v2 = self(self, i + 1, r);
			ret = max(ret, v1 + v2);
		}
		vector dp(r - l + 1, -(1 << 30));
		for (int i = l; i <= r; i++) {
			if (c[i] > l) continue;
			dp[i - l] = self(self, l, i - 1) + (r - l + 1);
			for (int j = l; j <= i - 1; j++) {
				int val = dp[j - l] + self(self, j + 1, i - 1) + (r - l + 1);
				dp[i - l] = max(dp[i - l], val);
			}
			ret = max(ret, dp[i - l] + self(self, i + 1, r));
		}
		return ret;
	};
	return rec(rec, 0, n - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, v) << '\n';
}