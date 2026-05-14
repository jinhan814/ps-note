#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

auto sol = [](int n, auto v) {
	vector dp(3'001, vector(3'001, 0));
	vector s1(3'001, 0);
	vector s2(3'001, 0);
	auto push = [&](int i, int j, int x) {
		dp[i][j] = add(dp[i][j], x);
		s1[i] = add(s1[i], x);
		s2[j] = add(s2[j], x);
	};
	auto pop = [&](int i, int j, int x) {
		dp[i][j] = sub(dp[i][j], x);
		s1[i] = sub(s1[i], x);
		s2[j] = sub(s2[j], x);
	};
	push(0, 0, 1);
	for (int i = 2; i <= n; i++) {
		if (v[i - 1] == v[i]) return 0;
	}
	for (int iter = n - 1; iter >= 2; iter--) {
		int prv = v[iter + 1];
		int cur = v[iter];
		int acc = 0;
		vector val(3'001, 0);
		for (int i = 0; i <= 3'000; i++) {
			pop(cur, i, dp[cur][i]);
			pop(i, cur, dp[i][cur]);
		}
		for (int i = 0; i <= 3'000; i++) {
			acc = add(acc, s1[i]);
			val[i] = add(s1[i], s2[i]);
		}
		for (int i = 0; i <= 3'000; i++) {
			push(prv, i, val[i]);
		}
		push(prv, prv, acc);
	}
	int ret = 0;
	for (int i = 0; i <= 3'000; i++) ret = add(ret, s1[i]);
	ret = sub(ret, s1[v[1]]);
	ret = sub(ret, s2[v[1]]);
	ret = add(ret, dp[v[1]][v[1]]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}