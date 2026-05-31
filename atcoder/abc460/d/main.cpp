#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	for (int iter = 0; iter < 2; iter++) {
		vector c(n, string(m, '.'));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (v[i][j] == '#') continue;
				for (int k = 0; k < 8; k++) {
					int nx = i + "10001222"[k] - '1';
					int ny = j + "22100012"[k] - '1';
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
					if (v[nx][ny] != '#') continue;
					c[i][j] = '#';
					break;
				}
			}
		}
		v.swap(c);
	}
	vector d(n, vector(m, -1));
	vector q(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] == '.') continue;
			d[i][j] = 0;
			q.push_back(pair(i, j));
		}
	}
	while (q.size()) {
		vector nq(0, pair(0, 0));
		for (auto [x, y] : q) {
			for (int k = 0; k < 8; k++) {
				int nx = x + "10001222"[k] - '1';
				int ny = y + "22100012"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (d[nx][ny] != -1) continue;
				d[nx][ny] = d[x][y] + 1;
				nq.push_back(pair(nx, ny));
			}
		}
		q.swap(nq);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (d[i][j] == -1) continue;
			if (d[i][j] % 2 == 1) continue;
			v[i][j] = '#';
		}
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, m, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}