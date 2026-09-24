#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string a, string b) {
	for (int i = 0; i < n; i++) {
		if (b[i] == '*') continue;
		if (a[i] != b[i]) return false;
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string a, b; cin >> a >> b;
	cout << (sol(n, a, b) ? "Yes" : "No") << '\n';
}