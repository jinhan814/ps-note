#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	vector cnt(26, 0);
	for (char c : s) cnt[c - 'a']++;
	int mx = *max_element(cnt.begin(), cnt.end());
	string ret;
	for (char c : s) if (cnt[c - 'a'] != mx) ret.push_back(c);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}