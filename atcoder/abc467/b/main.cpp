#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int res = 0;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		string s; cin >> s;
		if (s == "keep") res += b - a;
	}
	cout << res << '\n';
}