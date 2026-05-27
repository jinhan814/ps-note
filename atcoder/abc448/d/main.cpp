#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v, auto adj) {
	auto c = v;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	for (int i = 1; i <= n; i++) {
		auto it = lower_bound(c.begin(), c.end(), v[i]);
		v[i] = it - c.begin();
	}
	vector ret(n + 1, false);
	vector cnt(c.size(), 0);
	auto rec = [&](const auto& self, int cur, int prv, bool f) -> void {
		cnt[v[cur]]++;
		if (cnt[v[cur]] >= 2) f = true;
		ret[cur] = f;
		for (int nxt : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur, f);
		}
		cnt[v[cur]]--;
	};
	rec(rec, 1, -1, false);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto res = sol(n, v, adj);
	for (int i = 1; i <= n; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}