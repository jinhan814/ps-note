#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto adj) {
	vector dp(n + 1, -1);
	auto rec = [&](const auto& self, int cur) -> int {
		if (cur == n) return 1;
		int& ret = dp[cur];
		if (ret != -1) return ret;
		ret = 0;
		for (int nxt : adj[cur]) ret = add(ret, self(self, nxt));
		return ret;
	};
	return rec(rec, 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector adj(n + 1, vector(0, 0));
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
		}
		cout << sol(n, m, adj) << '\n';
	}
}