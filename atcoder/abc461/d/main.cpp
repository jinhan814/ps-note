#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](auto v, int k) {
	if (k < 0) return 0;
	int ret = 0, acc = 0;
	for (int i = 0, j = 0; i < v.size(); acc -= v[i++]) {
		while (j < v.size() && acc + v[j] <= k) acc += v[j++];
		ret += j - i;
	}
	return ret;
};

auto sol = [](int n, int m, int k, auto v) {
	i64 ret = 0;
	for (int l = 0; l < m; l++) {
		vector c(n, 0);
		for (int r = l; r < m; r++) {
			for (int i = 0; i < n; i++) {
				if (v[i][r] == '0') continue;
				c[i]++;
			}
			ret += calc(c, k) - calc(c, k - 1);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}