#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int x = 0;
	for (int i = 0; i < n; i++) x += v[i];
	int res = 1 << 30;
	for (int i = 0; i < n - 1; i++) {
		x -= 2 * v[i];
		res = min(res, abs(x));
	}
	cout << res << '\n';
}