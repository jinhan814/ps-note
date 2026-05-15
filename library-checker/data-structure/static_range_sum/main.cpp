#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector p(n + 1, i64(0));
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		p[i] = p[i - 1] + x;
	}
	while (q--) {
		int l, r; cin >> l >> r;
		cout << p[r] - p[l] << '\n';
	}
}