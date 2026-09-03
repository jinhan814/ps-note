#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int ret = 0;
	for (int i = 0, j = 0, a = -1, b = 0; i < s.size(); i = j) {
		while (j < s.size() && s[i] == s[j]) j++;
		if (a == s[i] - 1) ret += min(b, j - i);
		a = s[i];
		b = j - i;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}