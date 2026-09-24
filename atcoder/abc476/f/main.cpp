#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto a, auto b) {
	vector p1(n + 2, vector(n + 2, i64(0)));
	vector p2(n + 2, vector(n + 2, i64(0)));
	vector c(n + 1, i64(0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int val = i64(a[i]) * b[j] % m;
			p1[i][j] = val + p1[i - 1][j - 1];
			p2[i][j] = val + p2[i - 1][j + 1];
			c[1] += i64(val) * max(i - 1, j - 1);
		}
	}
	for (int j = 2; j <= n; j++) {
		p1[n][j] += p1[n][j - 2];
	}
	for (int j = n - 2; j >= 1; j--) {
		p2[n][j] += p2[n][j + 2];
	}
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 1; j <= n; j++) {
			p1[i][j] += p1[i + 1][j - 1];
			p2[i][j] += p2[i + 1][j + 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = n; j >= 1; j--) {
			p1[i][j] += p1[i][j - 1];
		}
		for (int j = 1; j <= n; j++) {
			p2[i][j] += p2[i][j + 1];
		}
	}
	for (int i = 2; i <= n; i++) {
		c[i] = c[i - 1];
		c[i] += p1[1][i - 1];
		c[i] -= p1[n][n - i + 1];
	}
	i64 ret = 0;
	for (int i = 1; i <= n; i++) {
		ret ^= c[i] + i64(i - 1) * n;
	}
	for (int j = 2; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			c[i] += p1[i][j - 1];
			c[i] -= p2[i][j];
			ret ^= c[i] + i64(i - 1) * n + i64(j - 1);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}