#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector d(n * m + 1, pair(-1, -1));
	vector c(n * m + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i] == b[j]) d[a[i]] = pair(i, j);
			else c[min(a[i], b[j])].push_back(pair(i, j));
		}
	}
	vector v(n, vector(m, 0));
	vector buc(0, pair(0, 0));
	for (int x = n * m; x >= 1; x--) {
		for (auto p : c[x]) buc.push_back(p);
		if (d[x] != pair(-1, -1)) buc.push_back(d[x]);
		if (buc.empty()) return vector(0, vector(0, 0));
		auto [i, j] = buc.back();
		buc.pop_back();
		v[i][j] = x;
	}
	for (int i = 0; i < n; i++) {
		int mx = 0;
		for (int j = 0; j < m; j++) mx = max(mx, v[i][j]);
		if (mx != a[i]) return vector(0, vector(0, 0));
	}
	for (int j = 0; j < m; j++) {
		int mx = 0;
		for (int i = 0; i < n; i++) mx = max(mx, v[i][j]);
		if (mx != b[j]) return vector(0, vector(0, 0));
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector a(n, 0), b(m, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < m; i++) cin >> b[i];
		auto res = sol(n, m, a, b);
		if (res.size()) {
			cout << "Yes" << '\n';
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) cout << res[i][j] << ' ';
				cout << '\n';
			}
		}
		else {
			cout << "No" << '\n';
		}
	}
}