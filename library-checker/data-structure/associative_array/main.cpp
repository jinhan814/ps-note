#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	map v{ pair(i64(0), i64(0)) };
	while (q--) {
		int op; cin >> op;
		if (op == 0) {
			i64 a, b; cin >> a >> b;
			v[a] = b;
		}
		else {
			i64 p; cin >> p;
			cout << v[p] << '\n';
		}
	}
}