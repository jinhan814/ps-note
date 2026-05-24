#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s = "HelloWorld";
	s.erase(s.begin() + n - 1);
	cout << s << '\n';
}