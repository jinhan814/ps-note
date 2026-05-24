#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 2; i <= n; i++) {
		int p = -1;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (v[1][j] + v[j][i] != v[1][i]) continue;
			if (p == -1) p = j;
			if (v[p][i] > v[j][i]) p = j;
		}
		if (p == -1) return false;
		adj[p].push_back(pair(i, v[p][i]));
		adj[i].push_back(pair(p, v[p][i]));
	}
	vector d(n + 1, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		auto rec = [&](const auto& self, int cur, int prv) -> void {
			for (auto [nxt, cost] : adj[cur]) {
				if (nxt == prv) continue;
				d[i][nxt] = d[i][cur] + cost;
				self(self, nxt, cur);
			}
		};
		rec(rec, i, 0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (v[i][j] == d[i][j]) continue;
			return false;
		}
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int x; cin >> x;
			v[i][j] = x;
			v[j][i] = x;
		}
	}
	cout << (sol(n, v) ? "Yes" : "No") << '\n';
}