#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector d(n, vector(m, vector(4, -1)));
	vector p(n, vector(m, vector(4, tuple(-1, -1, -1))));
	deque q(0, tuple(0, 0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] != 'S') continue;
			for (int k = 0; k < 4; k++) {
				d[i][j][k] = 0;
				q.push_back(tuple(i, j, k));
			}
		}
	}
	while (q.size()) {
		auto [x, y, i] = q.front(); q.pop_front();
		if (v[x][y] == 'G') {
			string ret;
			while (v[x][y] != 'S') {
				auto [nx, ny, k] = p[x][y][i];
				if (nx + 1 == x) ret.push_back('D');
				else if (nx - 1 == x) ret.push_back('U');
				else if (ny + 1 == y) ret.push_back('R');
				else ret.push_back('L');
				x = nx;
				y = ny;
				i = k;
			}
			reverse(ret.begin(), ret.end());
			return ret;
		}
		for (int k = 0; k < 4; k++) {
			if (v[x][y] == 'o' && k != i) continue;
			if (v[x][y] == 'x' && k == i) continue;
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (v[nx][ny] == '#') continue;
			if (d[nx][ny][k] != -1) continue;
			d[nx][ny][k] = d[x][y][i] + 1;
			p[nx][ny][k] = tuple(x, y, i);
			q.push_back(tuple(nx, ny, k));
		}
	}
	return string(0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, m, v);
	if (res.size()) {
		cout << "Yes" << '\n';
		cout << res << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}