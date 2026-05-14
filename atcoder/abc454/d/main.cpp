#include <bits/stdc++.h>
using namespace std;

auto conv = [](string s) {
	string t;
	for (char c : s) {
		t.push_back(c);
		if (t.size() < 4) continue;
		if (t.substr(t.size() - 4) != "(xx)") continue;
		t.pop_back();
		t.pop_back();
		t.pop_back();
		t.pop_back();
		t.push_back('x');
		t.push_back('x');
	}
	return t;
};

auto sol = [](string a, string b) {
	return conv(a) == conv(b);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string a, b; cin >> a >> b;
		cout << (sol(a, b) ? "Yes" : "No") << '\n';
	}
}