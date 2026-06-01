#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << (s[0] == s[1] && s[0] == s[2] ? "Yes" : "No") << '\n';
}