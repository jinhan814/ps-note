#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	i64 s = 0, x = 0;
	for (int i = 1; i <= n; i++) {
		s += v[i];
		x ^= v[i];
	}
	if (x == 0) {
		int opt = -1;
		for (int i = 1; i <= n; i++) {
			if (opt == -1 || (v[opt] & -v[opt]) > (v[i] & -v[i])) opt = i;
		}
		return tuple(s, opt, i64(1));
	}
	else {
		int opt = -1;
		for (int i = 1; i <= n; i++) {
			i64 val = x ^ v[i];
			if (val >= v[i]) continue;
			if (opt == -1 || v[opt] - (x ^ v[opt]) < v[i] - val) opt = i;
		}
		i64 val = v[opt] - (x ^ v[opt]);
		return tuple(s - val + 1, opt, val);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, i64(0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto [opt, pos, val] = sol(n, v);
	cout << opt << '\n';
	cout << pos << ' ' << val << '\n';
}