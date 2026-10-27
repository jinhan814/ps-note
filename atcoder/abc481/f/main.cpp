#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

auto sol = [](int n, int m, auto adj) {
	vector ret(n + 1, 0);
	vector v(n + 1, 1 << 30);
	vector d(n + 1, -1); d[1] = 0;
	vector q(1, 1);
	while (q.size()) {
		vector c(0, 0);
		for (int i : q) c.push_back(v[i]);
		sort(c.begin(), c.end());
		for (int i : q) v[i] = lower_bound(c.begin(), c.end(), v[i]) - c.begin();
		vector nq(0, 0);
		for (int cur : q) {
			for (auto [nxt, x] : adj[cur]) {
				if (d[nxt] == -1) d[nxt] = d[cur] + 1, nq.push_back(nxt);
				if (d[nxt] != d[cur] + 1) continue;
				if (v[nxt] <= v[cur] * 10 + x) continue;
				ret[nxt] = (i64(ret[cur]) * 10 + x) % mod;
				v[nxt] = v[cur] * 10 + x;
			}
		}
		q.swap(nq);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
	}
	auto res = sol(n, m, adj);
	for (int i = 2; i <= n; i++) cout << res[i] << '\n';
}