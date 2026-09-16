#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << s[0];
	for (int i = 1; i < s.size(); i++) cout << 'o' << s[i];
	cout << '\n';
}