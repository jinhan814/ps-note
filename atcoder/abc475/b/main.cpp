#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		x = 100'000 - x;
		a += x % 10;
		b += x / 10 % 10;
		c += x / 100 % 10;
	}
	cout << a << ' ' << b << ' ' << c << '\n';
}