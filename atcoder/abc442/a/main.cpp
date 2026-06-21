#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int res = 0;
	for (char c : s) {
		if (c != 'i' && c != 'j') continue;
		res++;
	}
	cout << res << '\n';
}