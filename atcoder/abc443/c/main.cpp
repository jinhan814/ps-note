#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int ret = m;
	for (int i = 0, j = 0; i < n; i = j) {
		int lim = min(v[i] + 100, m);
		ret -= lim - v[i];
		while (j < n && v[j] <= lim) j++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}