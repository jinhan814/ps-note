#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n, int m) {
	if (m == 1) {
		return vector(1, 1);
	}
	if (n == 1) {
		vector ret(m, -1);
		ret[1] = 1;
		return ret;
	}
	vector p(0, 0);
	for (int i = 2; i64(i) * i <= n; i++) {
		if (n % i != 0) continue;
		while (n % i == 0) n /= i, p.push_back(i % m);
	}
	if (n > 1) p.push_back(n % m);
	vector d(m, vector(p.size(), 1 << 30)); d[1][0] = 0;
	deque dq(1, pair(1, 0));
	while (dq.size()) {
		auto [i, j] = dq.front(); dq.pop_front();
		int nj = j + 1 < p.size() ? j + 1 : 0;
		int val = d[i][j] + (j == 0);
		for (int ni : { i64(i), i64(i) * p[j] % m }) {
			if (d[ni][nj] <= val) continue;
			d[ni][nj] = val;
			if (j == 0) dq.push_back(pair(ni, nj));
			else dq.push_front(pair(ni, nj));
		}
	}
	vector ret(m, -1);
	for (int i = 0; i < m; i++) {
		int mn = *min_element(d[i].begin(), d[i].end());
		if (mn < 1) mn = 1;
		if (mn != 1 << 30) ret[i] = mn;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	int m; cin >> m;
	auto res = sol(n, m);
	for (int i = 0; i < m; i++) cout << res[i] << '\n';
}