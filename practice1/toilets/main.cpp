#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n, int m, auto v, auto c) {
	i64 mx = 0, acc = 0;
	for (int i = 0; i < m; i++) {
		i64 psum = 0, val = 0;
		for (int j = 0; j < v[i].size(); j++) {
			if (v[i][j] == 'F') psum++;
			else psum--, val = max(val, acc + psum);
		}
		if (psum > 0) val += psum * (c[i] - 1);
		mx = max(mx, val);
		acc += psum * c[i];
	}
	if (acc < 0) return i64(-1);
	return max(mx - acc, i64(0));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	int m; cin >> m;
	vector v(m, string{});
	vector c(m, i64(0));
	for (int i = 0; i < m; i++) cin >> v[i] >> c[i];
	cout << sol(n, m, v, c) << '\n';
}