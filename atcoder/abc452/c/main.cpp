#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v, auto c) {
	auto f = [&](string s) {
		if (s.size() != n) return false;
		for (int i = 0; i < n; i++) {
			bool flag = false;
			for (int j = 0; j < m; j++) {
				if (c[j].size() != v[i][0]) continue;
				if (c[j][v[i][1] - 1] != s[i]) continue;
				flag = true;
				break;
			}
			if (!flag) return false;
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