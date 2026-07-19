#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	string t;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] != 'A') {
			t.push_back(s[i]);
		}
		else {
			if (t.empty() || t.back() != 'B') continue;
			t.pop_back();
			if (t.empty() || t.back() != 'C') continue;
			t.pop_back();
		}
	}
	return t.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string s; cin >> s;
		cout << sol(s) << '\n';
	}
}