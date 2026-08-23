#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b) {
	if (a + b == 9) return true;
	if (a - b == 9) return true;
	if (a * b == 9) return true;
	if (a % b == 0 && a / b == 9) return true;
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b; cin >> a >> b;
	cout << (sol(a, b) ? "Nine" : "Nein") << '\n';
}