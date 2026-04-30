#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 119 << 23 | 1;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, string s, auto v) {
	vector dp(26, 0);
	for (int i = 0; i < n; i++) {
		int p = s[i] - 'a';
		int x = 1;
		for (int j = 0; j < 26; j++) {
			if (j == p) continue;
			x = add(x, dp[j]);
		}
		dp[p] = add(dp[p], mul(x, v[i]));
	}
	int ret = 0;
	for (int i = 0; i < 26; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s(n, 0);
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> s[i] >> v[i];
	cout << sol(n, s, v) << '\n';
}