#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector c(n + 1, 0);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		c[x]++;
	}
	int res = n;
	for (int i = 1; i <= n; i++) res = min(res, n - c[i]);
	cout << res << '\n';
}