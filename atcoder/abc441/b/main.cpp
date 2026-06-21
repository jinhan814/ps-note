#include <bits/stdc++.h>
using namespace std;

auto sol = [](string a, string b, string s) {
	vector ca(26, false);
	vector cb(26, false);
	for (char c : a) ca[c - 97] = true;
	for (char c : b) cb[c - 97] = true;
	bool fa = true;
	bool fb = true;
	for (char c : s) {
		if (!ca[c - 97]) fa = false;
		if (!cb[c - 97]) fb = false;
	}
	if (fa && !fb) return string("Takahashi");
	if (!fa && fb) return string("Aoki");
	return string("Unknown");
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string a, b; cin >> a >> b;
	int q; cin >> q;
	while (q--) {
		string s; cin >> s;
		cout << sol(a, b, s) << '\n';
	}
}