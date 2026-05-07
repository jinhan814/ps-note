#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
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

auto sol = [](int n, int m, int k, auto v) {
	vector fac(n + m + 1, 1);
	for (int i = 1; i <= n + m; i++) {
		fac[i] = mul(fac[i - 1], i);
	}
	vector inv(n + m + 1, pow(fac[n + m], mod - 2));
	for (int i = n + m; i >= 1; i--) {
		inv[i - 1] = mul(inv[i], i);
	}
	auto bino = [&](int n, int k) {
		if (k == 0 || k == n) return 1;
		return mul(fac[n], mul(inv[k], inv[n - k]));
	};
	sort(v.begin(), v.end());
	v.push_back(pair(n, m));
	vector dp(k + 1, 0);
	for (int i = 0; i <= k; i++) {
		dp[i] = bino(v[i].first + v[i].second - 2, v[i].first - 1);
		for (int j = 0; j < i; j++) {
			if (v[j].second > v[i].second) continue;
			int dx = v[i].first - v[j].first;
			int dy = v[i].second - v[j].second;
			dp[i] = sub(dp[i], mul(dp[j], bino(dx + dy, dx)));
		}
	}
	return dp[k];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, pair(0, 0));
	for (auto& [x, y] : v) cin >> x >> y;
	cout << sol(n, m, k, v) << '\n';
}