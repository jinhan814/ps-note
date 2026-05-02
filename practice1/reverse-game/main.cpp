#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int acc = 0, cnt = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') acc = (acc + cnt) %3;
		else cnt++;
	}
	return acc != 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << (sol(s) ? "Alice" : "Bob") << '\n';
}