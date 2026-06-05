#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector mx(n, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] != '#') continue;
			mx[j] = i;
		}
	}
	vector c(n, vector(n, false)); c[n - 1][k - 1] = true;
	vector q(1, pair(n - 1, k - 1));
	while (q.size()) {
		auto [x, y] = q.back(); q.pop_back();
		if (x == 0) continue;
		for (int ny = y - 1; ny <= y + 1; ny++) {
			if (ny < 0 || ny >= n) continue;
			if (v[x - 1][ny] == '.') {
				if (c[x - 1][ny]) continue;
				q.push_back(pair(x - 1, ny));
				c[x - 1][ny] = true;
			}
			else {
				if (mx[ny] != x - 1) continue;
				for (int nx = 0; nx <= x - 1; nx++) {
					if (c[nx][ny]) continue;
					q.push_back(pair(nx, ny));
					c[nx][ny] = true;
				}
			}
		}
	}
	string ret(n, '0');
	for (int p = 0; p < n; p++) {
		if (!c[0][p]) continue;
		ret[p] = '1';
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, k; cin >> n >> k;
		vector v(n, string{});
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, k, v) << '\n';
	}
}