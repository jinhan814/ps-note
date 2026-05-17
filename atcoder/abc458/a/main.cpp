#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int n; cin >> n;
	cout << s.substr(n, s.size() - 2 * n) << '\n';
}