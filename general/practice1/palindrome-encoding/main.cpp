#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	while (s.size() >= 2 && s[0] == s[1]) s.erase(s.begin());
	for (int i = 1; i < s.size(); i++) {
		if (s[i - 1] != s[i]) continue;
		return i;
	}
	return (int)s.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}