#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	vector p(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		p[i] = p[i - 1];
		if (s[i - 1] == 'o') p[i]++;
	}
	vector ret(n + 1, 0);
	for (int i = 1, j = 1; i <= n; i++) {
		while (j < n && j < i + p[j]) j++;
		ret[i] = j;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	auto res = sol(n, s);
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}