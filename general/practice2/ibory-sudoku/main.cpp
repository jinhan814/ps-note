#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector c(n * n, false);
	vector p(n * n + 1, 0);
	for (int i = 0; i < n * n; i++) p[v[n * n - 1][i]] = i;
	int ret = 0;
	for (int i = 0; i < n * n; i++) {
		if (c[i]) continue;
		int j = i;
		while (!c[j]) c[j] = true, j = p[v[n * n - 2][j]];
		ret = n * n * (n * n - 2) + i + 1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n * n, vector(n * n, 0));
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) cin >> v[i][j];
	}
	cout << sol(n, v) << '\n';
}