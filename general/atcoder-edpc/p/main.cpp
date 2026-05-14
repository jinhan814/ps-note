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

auto sol = [](int n, auto adj) {
	vector dp(n + 1, array{ 1, 1 });
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			dp[cur][0] = mul(dp[cur][0], add(dp[nxt][0], dp[nxt][1]));
			dp[cur][1] = mul(dp[cur][1], dp[nxt][0]);
		}
	};
	rec(rec, 1, -1);
	return add(dp[1][0], dp[1][1]);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, adj) << '\n';
}