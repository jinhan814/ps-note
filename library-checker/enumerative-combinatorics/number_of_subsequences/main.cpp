#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, auto v) {
	auto c = v;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector dp(c.size(), 0);
	int acc = 0;
	for (int x : v) {
		x = lower_bound(c.begin(), c.end(), x) - c.begin();
		int val = add(acc, 1);
		acc = sub(acc, dp[x]);
		dp[x] = val;
		acc = add(acc, val);
	}
	return acc;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}