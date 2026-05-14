#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector g(n, vector(m, vector(n, vector(m, -1))));
	auto rec = [&](const auto& self, int x1, int y1, int x2, int y2) -> int {
		if (x1 > x2 || y1 > y2) return 0;
		int& ret = g[x1][y1][x2][y2];
		if (ret != -1) return ret;
		ret = 0;
		bitset<512> b;
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				if (v[x][y] != '.') continue;
				int val = 0;
				val ^= self(self, x1, y1, x - 1, y - 1);
				val ^= self(self, x1, y + 1, x - 1, y2);
				val ^= self(self, x + 1, y1, x2, y - 1);
				val ^= self(self, x + 1, y + 1, x2, y2);
				b.set(val);
			}
		}
		while (b[ret]) ret++;
		return ret;
	};
	return rec(rec, 0, 0, n - 1, m - 1) != 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, m, v) ? "First" : "Second") << '\n';
}