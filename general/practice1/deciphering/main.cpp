#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 10'000'000;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto v, string s) {
	vector dp(26, 0);
	for (char c : s) {
		int val = 1;
		for (int i = 0; i < 26; i++) {
			if (v[i][c - 'A']) continue;
			val = add(val, dp[i]);
		}
		dp[c - 'A'] = val;
	}
	int ret = 0;
	for (int i = 0; i < 26; i++) ret = add(ret, dp[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	int m; cin >> m;
	vector v(26, vector(26, false));
	for (int i = 0; i < m; i++) {
		char a, b; cin >> a >> b;
		v[a - 'A'][b - 'A'] = true;
	}
	cout << sol(n, m, v, s) << '\n';
}