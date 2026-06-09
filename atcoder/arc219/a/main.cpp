#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	sort(v.begin(), v.end());
	for (int mask = 0; mask < 1 << min(m, 15); mask++) {
		string s(m, '0');
		for (int i = 0; i < min(m, 15); i++) {
			if (~mask >> i & 1) continue;
			s[i] ^= 1;
		}
		if (binary_search(v.begin(), v.end(), s)) continue;
		for (int i = 0; i < m; i++) s[i] ^= 1;
		return s;
	}
	return string(0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	string res = sol(n, m, v);
	if (res.size()) {
		cout << "Yes" << '\n';
		cout << res << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}