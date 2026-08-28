#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, int m, auto v) {
	int acc = 0;
	for (int i = 0; i < n; i++) acc += v[i];
	vector dp(n + 1, vector(m + 1, vector(n + 1, f64(-1))));
	auto rec = [&](const auto& self, int i, int j, int k) -> f64 {
		if (i == 0 || j == 0) return 0;
		if (k == 0) {
			if (i == 1) return 1;
			f64& ret = dp[i][j][k];
			if (ret != f64(-1)) return ret;
			f64 p1 = f64(1) / (2 * i - 1);
			f64 p2 = 1 - p1;
			ret = 0;
			ret += p1 * (self(self, i - 1, j, 0) + 1);
			ret += p2 * self(self, i, j - 1, 2);
			return ret;
		}
		else {
			if (i == k) return i;
			f64& ret = dp[i][j][k];
			if (ret != f64(-1)) return ret;
			f64 p1 = f64(k) / (2 * i - k);
			f64 p2 = (1 - p1) / (2 * i - k - 1);
			f64 p3 = k * p2;
			f64 p4 = 2 * (i - k - 1) * p2;
			ret = 0;
			ret += p1 * (self(self, i - 1, j, k - 1) + 1);
			ret += p2 * (self(self, i - 1, j, k) + 1);
			if (j >= 2) {
				ret += p3 * (self(self, i - 1, j - 1, k) + 1);
				if (i - k >= 2) ret += p4 * self(self, i, j - 1, k + 2);
			}
			return ret;
		}
	};
	f64 ret = rec(rec, n, m, 0);
	ret = ret * acc / n;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << fixed << setprecision(20);
	cout << sol(n, m, v) << '\n';
}