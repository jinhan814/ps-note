#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	vector c(2027, false);
	while (!c[n]) {
		c[n] = true;
		int x = 0;
		for (char c : to_string(n)) x += (c - 48) * (c - 48);
		n = x;
	}
	return n == 1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	cout << (sol(n) ? "Yes" : "No") << '\n';
}