#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		return a[2] < b[2];
	});
	vector c(n + 1, 0);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (c[v[i][0]] == 0) cnt++;
		c[v[i][0]]++;
	}
	vector ret(m + 1, 0);
	for (int i = 1, p = 0; i <= m; i++) {
		while (p < n && v[p][2] <= i) {
			if (v[p][2] == i) {
				c[v[p][0]]--;
				if (c[v[p][0]] == 0) cnt--;
				if (c[v[p][1]] == 0) cnt++;
				c[v[p][1]]++;
			}
			p++;
		}
		ret[i] = cnt;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [a, b, c] : v) cin >> a >> c >> b;
	auto res = sol(n, m, v);
	for (int i = 1; i <= m; i++) cout << res[i] << '\n';
}