#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	string ret;
	for (string s : v) {
		if (s[0] <= 'c') ret.push_back('2');
		else if (s[0] <= 'f') ret.push_back('3');
		else if (s[0] <= 'i') ret.push_back('4');
		else if (s[0] <= 'l') ret.push_back('5');
		else if (s[0] <= 'o') ret.push_back('6');
		else if (s[0] <= 's') ret.push_back('7');
		else if (s[0] <= 'v') ret.push_back('8');
		else ret.push_back('9');
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}