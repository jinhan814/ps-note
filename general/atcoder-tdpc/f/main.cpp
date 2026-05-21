#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, int k) {
	deque dp(k, 0);
	dp[1] = 1;
	int acc = 1;
	for (int iter = 2; iter <= n - 1; iter++) {
		dp.push_front(acc);
		acc = add(acc, sub(acc, dp.back()));
		dp.pop_back();
	}
	acc = sub(acc, dp.back());
	return acc;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	cout << sol(n, k) << '\n';
}