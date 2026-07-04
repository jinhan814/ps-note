#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int x, y; cin >> x >> y;
	int a, b, c, d; cin >> a >> b >> c >> d;
	int res = 0;
	for (int i = c; i < d; i++) {
		if (a <= i && i < b) res += x;
		else res += y;
	}
	cout << res << '\n';
}