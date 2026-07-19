#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	string t;
	for (int i = s.size() - 1; i >= 0; i--) {
		t.push_back(s[i]);
		int p = 0;
		while (p < 3 && t.size() >= p + 1 && t[t.size() - (p + 1)] == "ABC"[p]) p++;
		while (p--) t.pop_back();
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