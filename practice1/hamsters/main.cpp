#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](const string& s, const string& t) {
	int sz = min(s.size() - 1, t.size());
	auto f = [&](int i) {
		if (i < sz) return t[i];
		if (i == sz) return '$';
		return s[s.size() - sz + i - sz - 1];
	};
	vector dp(2 * sz + 1, 0);
	for (int i = 1, j = 0; i <= 2 * sz; i++) {
		while (j && f(i) != f(j)) j = dp[j - 1];
		if (f(i) == f(j)) dp[i] = ++j;
	}
	return t.size() - dp[2 * sz];
};

auto matmul = [](int n, const auto& a, const auto& b) {
	vector c(n, vector(n, 1LL << 60));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
	}
	return c;
};

auto sol = [](int n, int k, auto v) {
	vector a(n, vector(n, 1LL << 60));
	vector b(n, vector(n, 0LL));
	for (int i = 0; i < n; i++) {
		a[i][i] = v[i].size();
		for (int j = 0; j < n; j++) b[i][j] = calc(v[i], v[j]);
	}
	for (int x = k - 1; x; x >>= 1) {
		if (x & 1) a = matmul(n, a, b);
		b = matmul(n, b, b);
	}
	i64 ret = 1LL << 60;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) ret = min(ret, a[i][j]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}