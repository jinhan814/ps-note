#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		if (i % 3 == 0) cout << "Fizz" << '\n';
		else cout << i << '\n';
	}
}