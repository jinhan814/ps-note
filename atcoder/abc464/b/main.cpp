#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int mn1 = n, mx1 = -1;
	int mn2 = m, mx2 = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] == '.') continue;
			mn1 = min(mn1, i);
			mx1 = max(mx1, i);
			mn2 = min(mn2, j);
			mx2 = max(mx2, j);
		}
	}
	vector ret(mx1 - mn1 + 1, string(mx2 - mn2 + 1, '.'));
	for (int i = mn1; i <= mx1; i++) {
		for (int j = mn2; j <= mx2; j++) {
			if (v[i][j] == '.') continue;
			ret[i - mn1][j - mn2] = '#';
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, m, v);
	for (int i = 0; i < res.size(); i++) cout << res[i] << '\n';
}