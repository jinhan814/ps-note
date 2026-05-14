#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	auto f = [&](int x1, int y1, int x2, int y2) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				char v1 = v[i][j];
				char v2 = v[x1 + x2 - i][y1 + y2 - j];
				if (v1 != v2) return false;
			}
		}
		return true;
	};
	int ret = 0;
	for (int x1 = 0; x1 < n; x1++) {
		for (int y1 = 0; y1 < m; y1++) {
			for (int x2 = x1; x2 < n; x2++) {
				for (int y2 = y1; y2 < m; y2++) {
					if (!f(x1, y1, x2, y2)) continue;
					ret++;
				}
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}