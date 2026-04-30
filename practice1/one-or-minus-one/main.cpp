#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector ret(n, vector(m, 0));
	vector psum(m + 1, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) psum[j + 1] = psum[j] + v[i][j];
		int p = 0;
		while (2 * psum[p] != psum[m]) p++;
		for (int j = 0; j < p; j++) ret[i][j] = 1;
		for (int j = p; j < m; j++) ret[i][j] = -1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> m >> n;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	auto res = sol(n, m, v);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
}