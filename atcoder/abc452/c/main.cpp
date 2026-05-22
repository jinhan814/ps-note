#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v, auto c) {
	vector p(11, vector(10, 0));
	for (string s : c) {
		for (int i = 0; i < s.size(); i++) {
			p[s.size()][i] |= 1 << (s[i] - 'a');
		}
	}
	auto f = [&](string s) {
		if (s.size() != n) return false;
		for (int i = 0; i < n; i++) {
			if (p[v[i][0]][v[i][1] - 1] >> (s[i] - 'a') & 1) continue;
			return false;
		}
		return true;
	};
	vector ret(m, false);
	for (int i = 0; i < m; i++) ret[i] = f(c[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	int m; cin >> m;
	vector c(m, string{});
	for (int i = 0; i < m; i++) cin >> c[i];
	auto res = sol(n, m, v, c);
	for (int i = 0; i < m; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}