#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector c(2 * m, i64(0));
	for (int i = 0; i < n; i++) {
		c[i % (2 * m)] += v[i];
	}
	i64 acc = 0;
	for (int i = 0; i < m; i++) acc += c[i];
	i64 ret = i64(1) << 60;
	for (int i = 0; i < 2 * m; i++) {
		ret = min(ret, acc);
		acc += c[(i + m) % (2 * m)] - c[i];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, m, v) << '\n';
	}
}