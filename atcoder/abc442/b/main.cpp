#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	bool flag = false;
	int x = 0;
	while (q--) {
		int op; cin >> op;
		if (op == 1) x++;
		else if (op == 2) x = max(x - 1, 0);
		else flag = !flag;
		if (flag && x >= 3) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
}