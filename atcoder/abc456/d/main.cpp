#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s) {
	array dp{ 0, 0, 0 };
	for (char c : s) {
		if (c == 'a') {
			dp[0] = add(dp[0], 1);
			dp[0] = add(dp[0], dp[1]);
			dp[0] = add(dp[0], dp[2]);
		}
		else if (c == 'b') {
			dp[1] = add(dp[1], 1);
			dp[1] = add(dp[1], dp[0]);
			dp[1] = add(dp[1], dp[2]);
		}
		else {
			dp[2] = add(dp[2], 1);
			dp[2] = add(dp[2], dp[0]);
			dp[2] = add(dp[2], dp[1]);
		}
	}
	int ret = 0;
	for (int i = 0; i < 3; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}