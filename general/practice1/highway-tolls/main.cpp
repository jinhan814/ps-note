#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto adj) {
	vector rev(n + 1, vector(0, array{ 0, 0, 0 }));
	for (int i = 1; i <= n; i++) {
		for (auto [j, c, d] : adj[i]) {
			rev[j].push_back(array{ i, c, d });
		}
	}
	vector dp1(n + 1, vector((n + 1) / 2 + 1, i64(1) << 60));
	vector dp2(n + 1, vector((n + 1) / 2 + 1, i64(1) << 60));
	dp1[1][0] = 0;
	dp2[n][0] = 0;
	for (int x = 1; x <= (n + 1) / 2; x++) {
		for (int i = 1; i <= n; i++) {
			for (auto [j, c, d] : adj[i]) {
				i64 val = dp1[i][x - 1] + i64(c) * k * x + d;
				dp1[j][x] = min(dp1[j][x], val);
			}
			for (auto [j, c, d] : rev[i]) {
				i64 val = dp2[i][x - 1] + i64(c) * k * (x - 1) + d;
				dp2[j][x] = min(dp2[j][x], val);
			}
		}
	}
	i64 ret = i64(1) << 60;
	for (int i = 1; i <= n; i++) {
		for (int x = 1; x <= (n + 1) / 2; x++) {
			ret = min(ret, dp1[i][x] + dp2[i][x]);
			ret = min(ret, dp1[i][x - 1] + dp2[i][x]);
		}
	}
	if (ret == i64(1) << 60) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector adj(n + 1, vector(0, array{ 0, 0, 0 }));
	for (int i = 0; i < m; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		adj[a].push_back(array{ b, c, d });
	}
	cout << sol(n, m, k, adj) << '\n';
}