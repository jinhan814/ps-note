#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	char c; cin >> c;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (s[c - 65] == 'o') flag = true;
	}
	cout << (flag ? "Yes" : "No") << '\n';
}