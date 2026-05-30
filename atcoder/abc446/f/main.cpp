#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto e) {
	vector adj(n + 1, vector(0, 0));
	vector rev(n + 1, vector(0, 0));
	for (auto [a, b] : e) {
		if (a == b) continue;
		adj[a].push_back(b);
		rev[b].push_back(a);
	}
	vector ret(n + 1, -1);
	vector a(n + 1, false);
	vector b(n + 1, false);
	int ca = 0;
	int cb = 0;
	for (int i = 1; i <= n; i++) {
		auto rec = [&](const auto& self, int cur) -> void {
			a[cur] = true, ca++;
			for (int nxt : adj[cur]) {
				if (!a[nxt] && nxt <= i) self(self, nxt);
				if (!b[nxt] && nxt > i) b[nxt] = true, cb++;
			}
		};
		bool flag = i == 1;
		for (int j : rev[i]) flag |= a[j];
		if (flag) rec(rec, i);
		if (b[i]) b[i] = false, cb--;
		if (ca == i) ret[i] = cb;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, array{ 0, 0 });
	for (int i = 0; i < m; i++) cin >> e[i][0] >> e[i][1];
	auto res = sol(n, m, e);
	for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}