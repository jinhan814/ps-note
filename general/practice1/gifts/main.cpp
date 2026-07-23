#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	auto conv = [](int x, int y, int k, auto buc) {
		vector ret(0, pair(0, 0));
		for (auto [a, b] : buc) {
			if (a < x - k) continue;
			if (b < y - k) continue;
			if (a + b < x + y - k) continue;
			ret.push_back(pair(a, b));
		}
		sort(ret.begin(), ret.end());
		return ret;
	};
	map cache{ pair(tuple(0, 0, 0, vector(0, pair(0, 0))), 0) };
	cache.clear();
	auto rec = [&](const auto& self, int x, int y, int k, auto buc) -> int {
		buc = conv(x, y, k, buc);
		if (cache.count(tuple(x, y, k, buc))) return cache[tuple(x, y, k, buc)];
		int ret = -1;
		if (x == n - 1 && y == m - 1) ret = 0;
		for (int d = 0; d < 4; d++) {
			int nx = x + "1201"[d] - '1';
			int ny = y + "2110"[d] - '1';
			int nk = k + "1100"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m || nk < 0) continue;
			if (v[nx][ny] == '#') continue;
			bool flag = binary_search(buc.begin(), buc.end(), pair(nx, ny));
			if (!flag) buc.push_back(pair(nx, ny));
			int res = self(self, nx, ny, nk, buc);
			if (!flag) buc.pop_back();
			if (res == -1) continue;
			if (!flag && v[nx][ny] != '.') res += v[nx][ny] - '0';
			ret = max(ret, res);
		}
		return cache[tuple(x, y, k, buc)] = ret;
	};
	int ret = rec(rec, 0, 0, k, vector(1, pair(0, 0)));
	if (v[0][0] != '.') ret += v[0][0] - '0';
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}