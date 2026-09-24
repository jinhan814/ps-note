#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	if (s.back() != 'e') s.push_back('e');
	s.push_back('r');
	cout << s << '\n';
}