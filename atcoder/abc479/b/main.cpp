#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	int ret = 0;
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && s[i] == s[j]) j++;
		if (s[i] == 'R') ret = max(ret, j - i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}