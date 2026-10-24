#include <bits/stdc++.h>
using namespace std;

auto sol = [](string a, string b) {
	if (b[0] == 'A' || b[1] == 'A') swap(a, b);
	if (a[1] == 'A') swap(a[0], a[1]), swap(b[0], b[1]);
	return a[1] == 'D' || b[0] == 'D';
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a, b; cin >> a >> b;
	cout << (sol(a, b) ? "Yes" : "No") << '\n';
}