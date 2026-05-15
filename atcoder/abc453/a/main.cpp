#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	while (s.size() && s[0] == 'o') s.erase(s.begin());
	cout << s << '\n';
}