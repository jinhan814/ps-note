#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b) {
	vector nxt(n, vector(n, pair(0, 0)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			nxt[i][j].first = j;
			nxt[i][j].second = (b * i + a * j) % n;
		}
	}
	vector c(n, vector(n, 0));
	vector d(n, vector(n, -1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (c[i][j] != 0) continue;
			int x = i, y = j;
			while (c[x][y] == 0) {
				c[x][y] = 1;
				tie(x, y) = nxt[x][y];
			}
			if (c[x][y] == 1) {
				int px = x, py = y;
				int val = 0;
				while (1) {
					if (x == 0 || y == 0) val = 1;
					tie(x, y) = nxt[x][y];
					if (x == px && y == py) break;
				}
				while (1) {
					d[x][y] = val;
					tie(x, y) = nxt[x][y];
					if (x == px && y == py) break;
				}
			}
			x = i, y = j;
			while (c[x][y] == 1) {
				c[x][y] = 2;
				tie(x, y) = nxt[x][y];
			}
		}
	}
	auto rec = [&](const auto& self, int i, int j) -> int {
		int& ret = d[i][j];
		if (ret != -1) return ret;
		ret = 0;
		if (i == 0 || j == 0) ret = 1;
		auto [x, y] = nxt[i][j];
		if (self(self, x, y)) ret = 1;
		return ret;
	};
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (rec(rec, i, j)) continue;
			ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	cout << sol(n, a, b) << '\n';
}