#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int acc = 0;
	for (int i = s.size() - 1, j = s.size() - 1; i >= 0; i--) {
		if (s[i] == '0') continue;
		acc = (acc + j - i) % 3;
		j--;
	}
	return acc != 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << (sol(s) ? "Alice" : "Bob") << '\n';
}