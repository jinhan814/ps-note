#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	sort(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') continue;
		swap(s[0], s[i]);
		break;
	}
	return s;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}