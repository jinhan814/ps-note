#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'A') a++;
		if (s[i] == 'B') b = min(a, b + 1);
		if (s[i] == 'C') c = min(b, c + 1);
	}
	return c;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}