#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, op; cin >> n >> op;
	if (op == 0) {
		cout << "! " << n / 2 << endl;
		for (int i = 1; i <= n / 2; i++) {
			int a, b; cin >> a >> b;
			assert(a != b);
			cout << b << ' ' << a << endl;
		}
	}
	else {
		cout << "! " << n / 2 + 1 << endl;
		cout << 1 << ' ' << 1 << endl;
		for (int i = 1; i <= n / 2 - 1; i++) {
			int a, b; cin >> a >> b;
			assert(a != b);
			cout << b << ' ' << a << endl;
		}
		int a, b; cin >> a >> b;
		assert(a == b);
	}
}