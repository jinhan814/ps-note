#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int ret = 0;
	for (int x = 0; x <= 1; x++) {
		for (int i = x; i < s.size(); i++) {
			int cnt = 0;
			for (int l = i - x, r = i; l >= 0 && r < s.size(); l--, r++) {
				if (s[l] != s[r]) cnt++;
				if (cnt > 1) break;
				ret++;
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}