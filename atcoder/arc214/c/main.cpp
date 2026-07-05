#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, auto v) {
	int acc = 0;
	for (int i = 0; i < n; i++) acc += v[i];
	if (acc % 2 == 1) return 0;
	acc /= 2;
	vector dp(acc + 1, 0); dp[0] = 1;
	for (int x : v) {
		for (int i = acc; i >= x; i--) {
			dp[i] = add(dp[i], dp[i - x]);
		}
	}
	return mul(dp[acc], add(dp[acc], mod - 2));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}