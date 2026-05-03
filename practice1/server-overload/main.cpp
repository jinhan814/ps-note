#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	vector c(1, 0LL);
	for (int i = 0; i < n; i++) {
		vector dp(5, vector(n / 3 + 1, 0LL));
		vector val(n / 3 + 1, 0LL);
		for (int a = 2; a < n; a++) {
			for (int b = 1; b <= (a + 1) / 3; b++) {
				i64 s = max(dp[0][b - 1], dp[1][b - 1]);
				i64 t = v[i][a - 2] + v[i][a - 1] + v[i][a];
				dp[4][b] = max(dp[3][b], s + t);
				val[b] = max(val[b], dp[4][b]);
			}
			for (int i = 1; i < 5; i++) swap(dp[i - 1], dp[i]);
		}
		int sz = c.size() - 1 + n / 3;
		if (sz > k) sz = k;
		vector nc(sz + 1, 0LL);
		auto rec = [&](const auto& self, int l, int r, int opt_l, int opt_r) -> void {
			if (l > r) return;
			int mid = l + r >> 1;
			int opt = -1;
			for (int i = opt_l; i <= opt_r; i++) {
				int j = mid - i;
				if (j < 0 || j >= c.size()) continue;
				if (opt == -1 || val[opt] + c[mid - opt] < val[i] + c[j]) opt = i;
			}
			nc[mid] = val[opt] + c[mid - opt];
			self(self, l, mid - 1, opt_l, opt);
			self(self, mid + 1, r, opt, opt_r);
		};
		rec(rec, 0, sz, 0, n / 3);
		c.swap(nc);
	}
	return c.back();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, vector(n, 0LL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> v[i][j];
	}
	cout << sol(n, k, v) << '\n';
}