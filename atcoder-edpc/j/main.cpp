#include <bits/stdc++.h>
using namespace std;

using f64 = double;

auto sol = [](int n, auto v) {
	int c1 = 0, c2 = 0, c3 = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] == 1) c1++;
		if (v[i] == 2) c2++;
		if (v[i] == 3) c3++;
	}
	vector dp(n + 1, vector(n + 1, vector(n + 1, f64(-1))));
	auto rec = [&](const auto& self, int a, int b, int c) -> f64 {
		if (a == 0 && b == 0 && c == 0) return 0;
		f64& ret = dp[a][b][c];
		if (ret != -1) return ret;
		ret = f64(n) / (a + b + c);
		if (a > 0) {
			f64 v1 = self(self, a - 1, b, c);
			f64 v2 = f64(a) / (a + b + c);
			ret += v1 * v2;
		}
		if (b > 0) {
			f64 v1 = self(self, a + 1, b - 1, c);
			f64 v2 = f64(b) / (a + b + c);
			ret += v1 * v2;
		}
		if (c > 0) {
			f64 v1 = self(self, a, b + 1, c - 1);
			f64 v2 = f64(c) / (a + b + c);
			ret += v1 * v2;
		}
		return ret;
	};
	return rec(rec, c1, c2, c3);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << fixed << setprecision(20);
	cout << sol(n, v) << '\n';
}