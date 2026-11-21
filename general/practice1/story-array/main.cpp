#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b, auto c, auto v) {
	auto cmp = [](auto a, auto b) { return a[1] < b[1]; };
	sort(a.begin(), a.end(), cmp);
	sort(b.begin(), b.end(), cmp);
	sort(c.begin(), c.end(), cmp);
	vector dp(n, vector(n + 1, vector(n + 1, vector(n + 1, array{ -1, -1, -1 }))));
	auto rec = [&](const auto& self, int iter, int i, int j, int k, int f) {
		if (i > n || j > n || k > n) return -(1 << 30);
		if (iter == n) return 0;
		int& ret = dp[iter][i][j][k][f];
		if (ret != -1) return ret;
		ret = max({
			self(self, iter, i + 1, j, k, f),
			self(self, iter, i, j + 1, k, f),
			self(self, iter, i, j, k + 1, f)
		});
		if (f != 0 && i < n && a[i][1] <= v[iter]) {
			ret = max(ret, self(self, iter + 1, i + 1, j, k, 0) + a[i][0]);
		}
		if (f != 1 && j < n && b[j][1] <= v[iter]) {
			ret = max(ret, self(self, iter + 1, i, j + 1, k, 1) + b[j][0]);
		}
		if (f != 2 && k < n && c[k][1] <= v[iter]) {
			ret = max(ret, self(self, iter + 1, i, j, k + 1, 2) + c[k][0]);
		}
		return ret;
	};
	int ret = max(rec(rec, 0, 0, 0, 0, 0), rec(rec, 0, 0, 0, 0, 1));
	if (ret < 0) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, array{ 0, 0 });
	vector b(n, array{ 0, 0 });
	vector c(n, array{ 0, 0 });
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
	for (int i = 0; i < n; i++) cin >> b[i][0] >> b[i][1];
	for (int i = 0; i < n; i++) cin >> c[i][0] >> c[i][1];
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, a, b, c, v) << '\n';
}