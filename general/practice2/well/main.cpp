#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v, auto adj) {
	i64 ret = 0;
	auto rec = [&](const auto& self, int cur, int prv) -> i64 {
		i64 mx = 0;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			i64 res = self(self, nxt, cur);
			v[cur] = max(v[cur] - res, i64(0));
			mx = max(mx, v[nxt] - res);
		}
		ret += mx;
		return mx;
	};
	i64 res = rec(rec, 1, -1);
	if (v[1] > res) ret += v[1] - res;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, m, v, adj) << '\n';
}