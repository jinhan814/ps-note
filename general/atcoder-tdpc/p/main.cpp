#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, int k, auto adj) {
	vector dp(n + 1, vector(k + 1, array{ 0, 0 }));
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		vector acc(k + 1, array{ 0, 0, 0 });
		acc[0][0] = 1;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			vector nacc(k + 1, array{ 0, 0, 0 });
			for (int i = 0; i <= k; i++) {
				for (int j = 0; i + j <= k; j++) {
					nacc[i + j][0] = add(nacc[i + j][0], mul(acc[j][0], dp[nxt][i][0]));
					nacc[i + j][1] = add(nacc[i + j][1], mul(acc[j][1], dp[nxt][i][0]));
					nacc[i + j][2] = add(nacc[i + j][2], mul(acc[j][2], dp[nxt][i][0]));
					nacc[i + j][1] = add(nacc[i + j][1], mul(acc[j][0], dp[nxt][i][1]));
					nacc[i + j][2] = add(nacc[i + j][2], mul(acc[j][1], dp[nxt][i][1]));
				}
			}
			acc.swap(nacc);
		}
		for (int i = 0; i <= k; i++) {
			dp[cur][i][0] = add(dp[cur][i][0], acc[i][0]);
			dp[cur][i][1] = add(dp[cur][i][1], acc[i][0]);
			dp[cur][i][1] = add(dp[cur][i][1], acc[i][1]);
			if (i > 0) {
				dp[cur][i][0] = add(dp[cur][i][0], acc[i - 1][1]);
				dp[cur][i][0] = add(dp[cur][i][0], acc[i - 1][2]);
			}
		}
	};
	rec(rec, 1, -1);
	return dp[1][k][0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, k, adj) << '\n';
}