#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int a, int b, auto v) {
	i64 ret = 0;
	for (int iter = 0; iter < 2; iter++) {
		for (int x1 = 0; x1 < n; x1++) {
			vector c(m, 1 << 30);
			for (int x2 = x1; x2 < n; x2++) {
				if (x2 - x1 + 1 > a) break;
				vector s(0, 0);
				for (int i = 0; i < m; i++) {
					c[i] = min(c[i], v[x2][i]);
					while (s.size() && c[s.back()] >= c[i]) {
						int val = c[s.back()];
						s.pop_back();
						int len = s.size() ? i - s.back() - 1 : i;
						if (len > b) len = b;
						i64 v1 = (x2 - x1 + 1) * len;
						i64 v2 = (i64(val) * n * m - 1) / (n * m - v1);
						ret = max(ret, v1 * v2);
					}
					s.push_back(i);
				}
				while (s.size()) {
					int val = c[s.back()];
					s.pop_back();
					int len = s.size() ? m - s.back() - 1 : m;
					if (len > b) len = b;
					i64 v1 = (x2 - x1 + 1) * len;
					i64 v2 = (i64(val) * n * m - 1) / (n * m - v1);
					ret = max(ret, v1 * v2);
				}
			}
		}
		swap(a, b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, a, b; cin >> a >> b >> n >> m;
	vector v(n, vector(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> v[i][j];
	}
	cout << sol(n, m, a, b, v) << '\n';
}