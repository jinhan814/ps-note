#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	set cache{ tuple(0, 0, 0, 0, 0, 0, 0) };
	cache.clear();
	auto rec = [&](const auto& self, int i, int j, int f, int b, int l, int r, int u) {
		if (i == 0 && j == 0) {
			if (f == -1) f = 0;
			if (b == -1) b = 0;
			if (l == -1) l = 0;
			if (r == -1) r = 0;
			if (u == -1) u = 0;
			return tuple(v[i][j], l, b, f, r, u);
		}
		if (cache.count(tuple(i, j, f, b, l, r, u))) {
			return tuple(-1, -1, -1, -1, -1, -1);
		}
		cache.insert(tuple(i, j, f, b, l, r, u));
		if (i > 0 && (b == -1 || b == v[i - 1][j])) {
			auto res = self(self, i - 1, j, v[i][j], u, l, r, f);
			if (res != tuple(-1, -1, -1, -1, -1, -1)) return res;
		}
		if (j > 0 && (l == -1 || l == v[i][j - 1])) {
			auto res = self(self, i, j - 1, f, b, u, v[i][j], r);
			if (res != tuple(-1, -1, -1, -1, -1, -1)) return res;
		}
		return tuple(-1, -1, -1, -1, -1, -1);
	};
	return rec(rec, n - 1, n - 1, -1, -1, -1, -1, -1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, vector(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cin >> v[i][j];
		}
		auto [a, b, c, d, e, f] = sol(n, v);
		if (a != -1) {
			cout << "Yes" << '\n';
			cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
		}
		else {
			cout << "No" << '\n';
		}
	}
}