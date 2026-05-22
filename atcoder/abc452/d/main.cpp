#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](string s, string t) {
	vector nxt(s.size() + 1, vector(26, s.size()));
	for (int i = s.size() - 1; i >= 0; i--) {
		nxt[i] = nxt[i + 1];
		nxt[i][s[i] - 'a'] = i;
	}
	i64 ret = 0;
	for (int i = 0; i < s.size(); i++) {
		bool flag = false;
		int p = i;
		for (char c : t) {
			if (nxt[p][c - 'a'] == s.size()) flag = true;
			else p = nxt[p][c - 'a'] + 1;
		}
		if (flag) ret += s.size() - i;
		else ret += p - i - 1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t; cin >> s >> t;
	cout << sol(s, t) << '\n';
}