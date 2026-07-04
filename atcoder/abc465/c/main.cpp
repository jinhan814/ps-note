#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	bool flag = false;
	deque v(0, 0);
	for (int i = 0; i < n; i++) {
		if (flag) v.push_front(i + 1);
		else v.push_back(i + 1);
		if (s[i] == 'o') flag = !flag;
	}
	if (flag) reverse(v.begin(), v.end());
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	auto res = sol(n, s);
	for (int x : res) cout << x << ' ';
	cout << '\n';
}