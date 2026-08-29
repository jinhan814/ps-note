#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector buc(26, vector(0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!isalpha(v[i][j])) continue;
			buc[v[i][j] - 'a'].push_back(i * m + j);
		}
	}
	vector d(n * m + 26, -1); d[0] = 0;
	deque dq(1, 0);
	while (dq.size()) {
		int cur = dq.front(); dq.pop_front();
		if (cur == n * m - 1) return d[cur];
		if (cur >= n * m) {
			for (int nxt : buc[cur - n * m]) {
				if (d[nxt] != -1) continue;
				d[nxt] = d[cur] + 1;
				dq.push_back(nxt);
			}
		}
		else {
			int x = cur / m;
			int y = cur % m;
			for (int i = 0; i < 4; i++) {
				int nx = x + "1012"[i] - '1';
				int ny = y + "2101"[i] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (v[nx][ny] == '#') continue;
				int nxt = nx * m + ny;
				if (d[nxt] == -1) d[nxt] = d[cur] + 1, dq.push_back(nxt);
			}
			if (isalpha(v[x][y])) {
				int nxt = v[x][y] - 'a' + n * m;
				if (d[nxt] == -1) d[nxt] = d[cur], dq.push_front(nxt);
			}
		}
	}
	return -1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}