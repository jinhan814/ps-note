#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	int cnt = 0;
	for (char c : s) if (c == 'o') cnt++;
	return string(cnt & 1 ? "odd" : "even");
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}