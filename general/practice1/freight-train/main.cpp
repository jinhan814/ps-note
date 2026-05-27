#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b, auto v) {
	int acc = 0;
	for (int i = n; i >= 2; i -= a) acc += 2 * (i - 1);
	b = min(b, acc);
	vector dp(a, vector(b + 1, -1));
	dp[0][b] = 0;
	for (int iter = n; iter >= 2; iter--) {
		auto ndp = dp;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j <= b; j++) {
				if (dp[i][j] == -1) continue;
				int ni = i + 1 < a ? i + 1 : 0;
				int nj = i == 0 ? j - 2 * (iter - 1) : j;
				if (nj < 0) continue;
				ndp[ni][nj] = max(ndp[ni][nj], dp[i][j] + v[iter]);
			}
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j <= b; j++) {
			ret = max(ret, dp[i][j]);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n + 1, 0);
	for (int i = 2; i <= n; i++) cin >> v[i];
	cout << sol(n, a, b, v) << '\n';
}