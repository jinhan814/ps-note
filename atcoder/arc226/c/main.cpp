#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m) {
	if (n % 2 == 0 || m % 2 == 0) {
		vector ret(0, tuple(0, 0, 0));
		for (int i = 1; i + 1 <= n; i += 2) {
			for (int j = 1; j + 1 <= m; j += 2) {
				ret.push_back(tuple(i, j, 1));
			}
		}
		return ret;
	}
	else {
		vector ret(0, tuple(0, 0, 0));
		for (int i = 1; i + 1 <= n; i += 2) {
			for (int j = n + 1; j + 1 <= m; j += 2) {
				ret.push_back(tuple(i, j, 1));
			}
		}
		for (int i = m + 1; i + 1 <= n; i += 2) {
			for (int j = 1; j + 1 <= m; j += 2) {
				ret.push_back(tuple(i, j, 1));
			}
		}
		for (int i = 0; i < (min(n, m) + 1) / 4; i++) {
			ret.push_back(tuple(1 + 2 * i, 1 + 2 * i, min(n, m) - 1 - 4 * i));
			for (int j = 0; j < (min(n, m) - 2 - 4 * i) / 2; j++) {
				ret.push_back(tuple(1 + 2 * i, 2 + 2 * i + 2 * j, 1));
				ret.push_back(tuple(min(n, m) - 1 - 2 * i, 3 + 2 * i + 2 * j, 1));
				ret.push_back(tuple(3 + 2 * i + 2 * j, 1 + 2 * i, 1));
				ret.push_back(tuple(2 + 2 * i + 2 * j, min(n, m) - 1 - 2 * i, 1));
			}
		}
		return ret;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		auto res = sol(n, m);
		cout << res.size() << '\n';
		for (auto [x, y, k] : res) cout << x << ' ' << y << ' ' << k << '\n';
	}
}