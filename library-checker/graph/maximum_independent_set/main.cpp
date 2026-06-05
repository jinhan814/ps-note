#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	if (n <= 2) return vector(1, 0);
	vector dp(1 << (n / 2), 0);
	vector prv(1 << (n / 2), -1);
	for (int mask = 0; mask < 1 << (n / 2); mask++) {
		bool flag = true;
		for (int i = 0; i < n / 2; i++) {
			if (~mask >> i & 1) continue;
			for (int j : adj[i]) {
				if (j >= n / 2) continue;
				if (~mask >> j & 1) continue;
				flag = false;
				break;
			}
			if (!flag) break;
		}
		if (!flag) continue;
		dp[mask] = __builtin_popcount(mask);
		prv[mask] = mask;
	}
	for (int bit = 0; bit < n / 2; bit++) {
		for (int mask = 0; mask < 1 << (n / 2); mask++) {
			if (~mask >> bit & 1) continue;
			if (dp[mask] >= dp[mask ^ 1 << bit]) continue;
			dp[mask] = dp[mask ^ 1 << bit];
			prv[mask] = prv[mask ^ 1 << bit];
		}
	}
	int opt1 = 0, opt2 = 0;
	for (int mask = 0; mask < 1 << ((n + 1) / 2); mask++) {
		bool flag = true;
		int s = (1 << (n / 2)) - 1;
		for (int i = n / 2; i < n; i++) {
			if (~mask >> (i - n / 2) & 1) continue;
			for (int j : adj[i]) {
				if (j < n / 2) {
					s &= ~(1 << j);
				}
				else {
					if (~mask >> (j - n / 2) & 1) continue;
					flag = false;
					break;
				}
			}
			if (!flag) break;
		}
		if (!flag) continue;
		int cnt = dp[s] + __builtin_popcount(mask);
		if (__builtin_popcount(opt1) + __builtin_popcount(opt2) >= cnt) continue;
		opt1 = prv[s];
		opt2 = mask;
	}
	vector ret(0, 0);
	for (int i = 0; i < n / 2; i++) {
		if (~opt1 >> i & 1) continue;
		ret.push_back(i);
	}
	for (int i = n / 2; i < n; i++) {
		if (~opt2 >> (i - n / 2) & 1) continue;
		ret.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto res = sol(n, m, adj);
	cout << res.size() << '\n';
	for (int i : res) cout << i << ' ';
	cout << '\n';
}