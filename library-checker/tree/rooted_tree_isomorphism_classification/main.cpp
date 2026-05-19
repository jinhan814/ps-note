#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector v(n, 0);
	map c{ pair(vector(0, 0), 0) }; c.clear();
	auto rec = [&](const auto& self, int cur) -> int {
		vector buc(0, 0);
		for (int nxt : adj[cur]) buc.push_back(self(self, nxt));
		sort(buc.begin(), buc.end());
		if (!c.count(buc)) c[buc] = c.size();
		return v[cur] = c[buc];
	};
	rec(rec, 0);
	return pair(c.size(), v);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int p; cin >> p;
		adj[p].push_back(i);
	}
	auto [k, res] = sol(n, adj);
	cout << k << '\n';
	for (int i = 0; i < n; i++) cout << res[i] << ' ';
	cout << '\n';
}