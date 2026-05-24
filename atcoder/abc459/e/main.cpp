#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

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

auto bino = [](i64 n, int k) {
	int a = 1, b = 1;
	for (int i = 0; i < k; i++) {
		a = mul(a, (n - i) % mod);
		b = mul(b, i + 1);
	}
	return mul(a, pow(b, mod - 2));
};

auto sol = [](int n, auto v, auto adj) {
	vector dp(n + 1, i64(0));
	auto rec = [&](const auto& self, int cur) -> void {
		dp[cur] = v[cur][0] - v[cur][1];
		for (int nxt : adj[cur]) {
			self(self, nxt);
			dp[cur] += dp[nxt];
		}
	};
	rec(rec, 1);
	int ret = 1;
	for (int i = 1; i <= n; i++) {
		if (dp[i] < 0) return 0;
		ret = mul(ret, bino(dp[i] + v[i][1], v[i][1]));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	vector adj(n + 1, vector(0, 0));
	for (int i = 2; i <= n; i++) {
		int p; cin >> p;
		adj[p].push_back(i);
	}
	for (int i = 1; i <= n; i++) cin >> v[i][0];
	for (int i = 1; i <= n; i++) cin >> v[i][1];
	cout << sol(n, v, adj) << '\n';
}