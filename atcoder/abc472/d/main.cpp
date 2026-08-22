#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector c1(n, false);
	vector c2(m, false);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[i][j] != '#') continue;
			c1[i] = true;
			c2[j] = true;
		}
	}
	vector d(n, vector(m, -1));
	vector q(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (c1[i] || c2[j]) continue;
			d[i][j] = 0;
			q.push_back(pair(i, j));
		}
	}
	int ret = q.size();
	for (int iter = 0; iter < k; iter++) {
		vector nq(0, pair(0, 0));
		for (auto [x, y] : q) {
			for (int i = 0; i < 4; i++) {
				int nx = x + "1012"[i] - '1';
				int ny = y + "2101"[i] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (v[nx][ny] == '#') continue;
				if (d[nx][ny] != -1) continue;
				d[nx][ny] = d[x][y] + 1;
				nq.push_back(pair(nx, ny));
			}
		}
		q.swap(nq);
		ret += q.size();
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}