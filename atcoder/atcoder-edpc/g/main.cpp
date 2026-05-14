#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	vector dp(n + 1, -1);
	auto rec = [&](const auto& self, int cur) -> int {
		int& ret = dp[cur];
		if (ret != -1) return ret;
		ret = 0;
		for (int nxt : adj[cur]) ret = max(ret, self(self, nxt) + 1);
		return ret;
	};
	int ret = -1;
	for (int i = 1; i <= n; i++) ret = max(ret, rec(rec, i));
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	cout << sol(n, m, adj) << '\n';
}