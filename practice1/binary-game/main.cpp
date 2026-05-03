#include <bits/stdc++.h>
using namespace std;

auto sol = [](string a, string b) {
	int v1 = 0, v2 = 0;
	for (char c : a) if (c == '1') v1++;
	for (char c : b) if (c == '1') v2++;
	if (v1 % 2 == 1) return v1 + 1 >= v2;
	return v1 >= v2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a, b; cin >> a >> b;
	cout << (sol(a, b) ? "VICTORY" : "DEFEAT") << '\n';
}