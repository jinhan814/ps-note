#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b) {
	if (a == 1 && b == 7) return true;
	if (a == 3 && b == 3) return true;
	if (a == 5 && b == 5) return true;
	if (a == 7 && b == 7) return true;
	if (a == 9 && b == 9) return true;
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b; cin >> a >> b;
	cout << (sol(a, b) ? "Yes" : "No") << '\n';
}