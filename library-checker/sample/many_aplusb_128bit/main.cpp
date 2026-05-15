#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

istream& operator>>(istream& in, i128 n) {
	string s; in >> s;
	n = 0;
	for (char c : s) {
		if (c == '-') continue;
		n = 10 * n + c - 48;
	}
	if (s[0] == '-') n = -n;
	return in;
}

ostream& operator<<(ostream& out, i128 n) {
	if (n < 0) out << '-', n = -n;
	string s;
	do s.push_back(n % 10 | 48); while (n /= 10);
	reverse(s.begin(), s.end());
	out << s;
	return out;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i128 a, b; cin >> a >> b;
		cout << a + b << '\n';
	}
}