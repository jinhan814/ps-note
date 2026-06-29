#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int cnt = count(s.begin(), s.end(), 'E');
	cout << (2 * cnt > s.size() ? "East" : "West") << '\n';
}