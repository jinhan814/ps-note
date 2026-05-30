#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	s[0] ^= 32;
	cout << "Of" << s << '\n';
}