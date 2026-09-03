#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b, int c) {
	if (a < b * c) return false;
	if ((a - b * c) % (c - 1)) return false;
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c; cin >> a >> b >> c;
	cout << (sol(a, b, c) ? "Yes" : "No") << '\n';
}