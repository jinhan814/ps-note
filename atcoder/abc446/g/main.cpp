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
	vector cnt(n + 1, 0);
	for (int i = 0; i < n; i++) {
		cnt[v[i]]++;
	}
	vector dp(n + 1, deque(0, 0));
	for (int i = 1; i <= n; i++) {
		if (cnt[i] < i) continue;
		dp[i].resize(i);
	}
	int acc = 0;
	for (int x : v) {
		if (cnt[x] < x) continue;
		acc = sub(acc, dp[x].back());
		dp[x].pop_back();
		dp[x].push_front(add(1, acc));
		acc = add(acc, dp[x].back());
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