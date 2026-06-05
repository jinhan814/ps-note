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

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](int n, auto adj) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	vector sz(n + 1, 1);
	vector dp(n + 1, 1);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			sz[cur] += sz[nxt];
			dp[cur] = mul(dp[cur], dp[nxt]);
			dp[cur] = mul(dp[cur], bino(sz[cur] - 1, sz[nxt]));
		}
	};
	auto reroot = [&](const auto& self, int cur, int prv) -> int {
		int ret = 0;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			int sz1 = sz[cur], sz2 = sz[nxt];
			int dp1 = dp[cur], dp2 = dp[nxt];
			dp[cur] = mul(dp[cur], pow(bino(sz[cur] - 1, sz[nxt]), mod - 2));
			dp[cur] = mul(dp[cur], pow(dp[nxt], mod - 2));
			sz[cur] -= sz[nxt];
			ret = add(ret, mul(mul(dp[cur], dp[nxt]), bino(sz[cur] + sz[nxt] - 2, sz[cur] - 1)));
			sz[nxt] += sz[cur];
			dp[nxt] = mul(dp[nxt], dp[cur]);
			dp[nxt] = mul(dp[nxt], bino(sz[nxt] - 1, sz[cur]));
			ret = add(ret, self(self, nxt, cur));
			sz[cur] = sz1;
			sz[nxt] = sz2;
			dp[cur] = dp1;
			dp[nxt] = dp2;
		}
		return ret;
	};
	rec(rec, 1, -1);
	return reroot(reroot, 1, -1);
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