#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector c(m + 1, false);
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		int res = 0;
		while (k--) {
			int x; cin >> x;
			if (!c[x] && res == 0) c[x] = true, res = x;
		}
		cout << res << '\n';
	}
}