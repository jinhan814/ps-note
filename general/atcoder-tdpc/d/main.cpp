#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using f64 = double;

auto sol = [](int n, i64 m) {
	int a = 0, b = 0, c = 0;
	while (m % 2 == 0) m /= 2, a++;
	while (m % 3 == 0) m /= 3, b++;
	while (m % 5 == 0) m /= 5, c++;
	if (m != 1) return f64(0);
	vector dp(a + 1, vector(b + 1, vector(c + 1, f64(0))));
	dp[0][0][0] = 1;
	for (int iter = 0; iter < n; iter++) {
		vector ndp(a + 1, vector(b + 1, vector(c + 1, f64(0))));
		for (int i = 0; i <= a; i++) {
			for (int j = 0; j <= b; j++) {
				for (int k = 0; k <= c; k++) {
					for (int x = 1; x <= 6; x++) {
						int ni = i, nj = j, nk = k;
						int val = x;
						while (val % 2 == 0) val /= 2, ni++;
						while (val % 3 == 0) val /= 3, nj++;
						while (val % 5 == 0) val /= 5, nk++;
						if (ni > a) ni = a;
						if (nj > b) nj = b;
						if (nk > c) nk = c;
						ndp[ni][nj][nk] += dp[i][j][k] / 6;
					}
				}
			}
		}
		dp.swap(ndp);
	}
	return dp[a][b][c];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 m; cin >> m;
	cout << fixed << setprecision(20);
	cout << sol(n, m) << '\n';
}