#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	int p = 1 << 30;
	for (int i = 0; i <= n; i++) {
		int x; cin >> x;
		if (abs(p - x) < m) continue;
		cout << i << ' ' << x << '\n';
		p = x;
	}
}