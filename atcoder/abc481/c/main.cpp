#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	map c{ pair(string(0, 0), 0) };
	while (q--) {
		string s; cin >> s;
		if (c.count(s) == 0) c[s] = c.size();
		cout << c[s] << '\n';
	}
}