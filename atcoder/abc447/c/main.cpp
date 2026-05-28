#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s, string t) {
	int ret = 0, i = 0, j = 0;
	while (i < s.size() && j < t.size()) {
		if (s[i] == t[j]) {
			i++;
			j++;
		}
		else {
			ret++;
			if (s[i] == 'A') i++;
			else if (t[j] == 'A') j++;
			else return -1;
		}
	}
	while (i < s.size()) {
		ret++;
		if (s[i] == 'A') i++;
		else return -1;
	}
	while (j < t.size()) {
		ret++;
		if (t[j] == 'A') j++;
		else return -1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t; cin >> s >> t;
	cout << sol(s, t) << '\n';
}