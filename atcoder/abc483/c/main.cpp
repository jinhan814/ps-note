#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector c(n + 1, 0);
	vector buc(n + 1, vector(0, 0));
	for (auto [a, b] : v) {
		c[a]++;
		buc[a].push_back(b);
	}
	auto f = [&](int i, int j) {
		if (i == -1 || j == -1) return i == -1;
		return c[i] < c[j] || (c[i] == c[j] && i > j);
	};
	int p1 = -1, p2 = -1;
	for (int i = 1; i <= n; i++) {
		if (f(p2, i)) p2 = i;
		if (f(p1, p2)) swap(p1, p2);
	}
	vector ret(n, 0);
	for (int i = 0; i < n; i++) {
		ret[i] = p1 != i + 1 ? p1 : p2;
		for (int p : buc[i + 1]) c[p]++;
		for (int p : buc[i + 1]) if (f(ret[i], p)) ret[i] = p;
		for (int p : buc[i + 1]) c[p]--;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, array{ 0, 0 });
	for (int i = 0; i < m; i++) cin >> v[i][0] >> v[i][1];
	auto res = sol(n, m, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}