#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int ret = 0;
	for (int i = 0; i < s.size(); i++) {
		int cnt = 0;
		for (int l = i, r = i; l >= 0 && r < s.size(); l--, r++) {
			if (s[l] != s[r]) cnt++;
			if (cnt > 1) break;
			ret++;
		}
	}
	for (int i = 1; i < s.size(); i++) {
		int cnt = 0;
		for (int l = i - 1, r = i; l >= 0 && r < s.size(); l--, r++) {
			if (s[l] != s[r]) cnt++;
			if (cnt > 1) break;
			ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}