#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] != 'x') continue;
		if (i - 1 >= 0 && s[i - 1] != 'x') continue;
		if (i + 1 < n && s[i + 1] != 'x') continue;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}