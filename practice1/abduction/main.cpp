#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 10'000'000;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, int m, int k, string s) {
	if (s[0] == 'R') {
		swap(n, m);
		for (char& c : s) c ^= 'L' ^ 'R';
	}
	vector dp1(n + 1, 0); dp1[0] = 1;
	vector dp2(m + 1, 1); dp2[0] = 0;
	for (int iter = 0, dir = 0; iter < k; iter++) {
		dir = (dir + (s[iter] == 'L' ? 1 : 3)) % 4;
		if (dir == 0) {
			vector ndp(m + 1, 0);
			for (int i = 0; i <= m - 1; i++) ndp[i + 1] = add(ndp[i], dp2[i]);
			dp2.swap(ndp);
		}
		else if (dir == 1) {
			vector ndp(n + 1, 0);
			for (int i = 0; i <= n - 1; i++) ndp[i + 1] = add(ndp[i], dp1[i]);
			dp1.swap(ndp);
		}
		else if (dir == 2) {
			vector ndp(m + 1, 0);
			for (int i = m; i >= 1; i--) ndp[i - 1] = add(ndp[i], dp2[i]);
			dp2.swap(ndp);
		}
		else {
			vector ndp(n + 1, 0);
			for (int i = n; i >= 1; i--) ndp[i - 1] = add(ndp[i], dp1[i]);
			dp1.swap(ndp);
		}
	}
	return mul(dp1[n], dp2[m]);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> m >> n >> k;
	string s; cin >> s;
	cout << sol(n, m, k, s) << '\n';
}