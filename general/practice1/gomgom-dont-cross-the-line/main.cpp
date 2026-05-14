#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, string s, string t) {
	i64 acc = 0;
	for (int i = 0, j = 0; i < s.size(); i++) {
		if (s[i] != '1') continue;
		while (t[j] != '1') j++;
		acc += abs(i - j);
		j++;
	}
	i64 v1 = acc / 2;
	i64 v2 = (acc + 1) / 2;
	return v1 * v1 + v2 * v2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s, t; cin >> s >> t;
	cout << sol(n, m, s, t) << '\n';
}