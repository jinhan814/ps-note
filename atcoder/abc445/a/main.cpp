#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << (s[0] == s.back() ? "Yes" : "No") << '\n';
}