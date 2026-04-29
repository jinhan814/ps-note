#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	vector buc(n, 0);
	iota(buc.begin(), buc.end(), 1);
	sort(buc.begin(), buc.end(), [&](int i, int j) {
		return adj[i].size() > adj[j].size();
	});
	vector c(n + 1, false);
	int sz = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j : adj[buc[i]]) {
			if (!c[j]) continue;
			cnt++;
		}
		if (cnt != i) break;
		c[buc[i]] = true;
		sz++;
	}
	vector cnt(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		sort(adj[i].begin(), adj[i].end());
		for (int j : adj[i]) {
			if (!c[i] && !c[j]) return 0;
			if (c[i] != c[j]) cnt[i]++;
		}
	}
	int ret = 1;
	for (int i = 1; i <= n; i++) {
		if (c[i]) {
			if (cnt[i] != 0) continue;
			ret++;
		}
		else {
			if (cnt[i] != sz - 1) continue;
			int p = 0;
			while (binary_search(adj[i].begin(), adj[i].end(), buc[p])) p++;
			if (cnt[buc[p]] != 0) continue;
			ret++;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << sol(n, m, adj) << '\n';
}