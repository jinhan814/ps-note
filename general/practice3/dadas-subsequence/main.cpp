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

auto sol = [](int n, auto v) {
	int ret = 0;
	vector dp(11, 0);
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		ret = mul(ret, 2);
		auto ndp = dp;
		for (int x = 0; x <= 10; x++) {
			int nx = max(v[i] - x, 0);
			ret = add(ret, mul(dp[x], nx));
			ndp[nx] = add(ndp[nx], dp[x]);
		}
		dp.swap(ndp);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}