#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, vector(m, 0));
	vector c(91, false);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		c[x] = true;
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < m; j++) if (c[v[i][j]]) cnt++;
		res = max(res, cnt);
	}
	cout << res << '\n';
}