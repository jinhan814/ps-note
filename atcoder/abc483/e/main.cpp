#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 ret = 0;
	for (int mask = 0; mask < 1 << m; mask++) {
		int pc = __builtin_popcount(mask);
		if (pc <= m - 3) continue;
		vector c(n, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (~mask >> j & 1) continue;
				c[i] = 26 * c[i] + v[i][j] - 'a';
			}
		}
		sort(c.begin(), c.end());
		i64 acc = 0;
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && c[i] == c[j]) j++;
			acc += i64(j - i) * (j - i - 1) / 2;
		}
		if (pc == m - 2) ret += acc;
		else if (pc == m - 1) ret -= acc * (m - 2);
		else ret += acc * (i64(m) * (m - 3) / 2 + 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}