#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto c, auto v) {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int x = min(c[v[i][0]], v[i][1]);
		c[v[i][0]] -= x;
		v[i][1] -= x;
		ret += x;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector c(m + 1, 0);
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= m; i++) cin >> c[i];
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, c, v) << '\n';
}