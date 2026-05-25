#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector c(n, vector(m, -1));
	int ord = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (c[i][j] != -1) continue;
			auto rec = [&](const auto& self, int x, int y) -> void {
				c[x][y] = ord;
				for (int d = 0; d < 4; d++) {
					int nx = x + "1012"[d] - '1';
					int ny = y + "2101"[d] - '1';
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
					if (v[nx][ny] != v[x][y]) continue;
					if (c[nx][ny] != -1) continue;
					self(self, nx, ny);
				}
			};
			rec(rec, i, j);
			ord++;
		}
	}
	vector f(ord, true);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int d = 0; d < 4; d++) {
				int nx = i + "1012"[d] - '1';
				int ny = j + "2101"[d] - '1';
				if (0 <= nx && nx < n && 0 <= ny && ny < m) continue;
				f[c[i][j]] = false;
				break;
			}
			if (v[i][j] == '#') f[c[i][j]] = false;
		}
	}
	int ret = 0;
	for (int i = 0; i < ord; i++) ret += f[i];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}