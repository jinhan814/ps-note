#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	i64 res = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != 'C') continue;
		res += min(i + 1, (int)s.size() - i);
	}
	cout << res << '\n';
}