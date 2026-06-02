#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	map c1{ pair(0, vector(0, 0)) };
	map c2{ pair(0, vector(0, 0)) };
	for (int i = 0; i < k; i++) {
		c1[v[i][0]].push_back(i);
		c2[v[i][1]].push_back(i);
	}
	vector ret(k, array{ 0, 0 });
	vector c(k, false);
	while (n > 0 && m > 0) {
		while (c1[n].size() && c[c1[n].back()]) c1[n].pop_back();
		while (c2[m].size() && c[c2[m].back()]) c2[m].pop_back();
		if (c1[n].size()) {
			int p = c1[n].back();
			c1[n].pop_back();
			m -= v[p][1];
			ret[p] = array{ 1, m + 1 };
			c[p] = true;
		}
		else {
			int p = c2[m].back();
			c2[m].pop_back();
			n -= v[p][0];
			ret[p] = array{ n + 1, 1 };
			c[p] = true;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	auto res = sol(n, m, k, v);
	for (auto [a, b] : res) cout << a << ' ' << b << '\n';
}