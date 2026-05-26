#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	while (q--) {
		int op, x; cin >> op >> x;
		if (op == 2) swap(n, m);
		cout << x * m << '\n';
		n -= x;
		if (op == 2) swap(n, m);
	}
}