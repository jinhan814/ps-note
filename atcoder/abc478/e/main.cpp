#include <bits/stdc++.h>
using namespace std;

auto get_scc = [](const auto& adj) {
	int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto dfs = [&](const auto& self, int cur) -> int {
		int ret = dfn[cur] = ++dfs_cnt;
		s.push_back(cur);
		for (int nxt : adj[cur]) {
			if (!dfn[nxt]) ret = min(ret, self(self, nxt));
			else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
		}
		if (ret == dfn[cur]) {
			scc_cnt++;
			while (s.size()) {
				int x = s.back(); s.pop_back();
				scc[x] = scc_cnt;
				if (x == cur) break;
			}
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
	return pair(scc_cnt, scc);
};

auto sol = [](int n, int q, auto qs) {
	vector adj(n + 1, vector(0, 0));
	for (auto [op, a, b] : qs) adj[a].push_back(b);
	auto [scc_cnt, scc] = get_scc(adj);
	vector buc(scc_cnt + 1, vector(0, 0));
	for (auto [op, a, b] : qs) {
		if (scc[a] == scc[b]) continue;
		buc[scc[a]].push_back(scc[b]);
	}
	vector c(scc_cnt + 1, 1);
	for (int i = scc_cnt; i >= 1; i--) {
		for (int j : buc[i]) c[j] = max(c[j], c[i] + 1);
	}
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) v[i] = c[scc[i]];
	for (auto [op, a, b] : qs) {
		if (op == 0 || v[a] < v[b]) continue;
		return vector(0, 0);
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [op, a, b] : qs) cin >> op >> a >> b;
	auto res = sol(n, q, qs);
	if (res.size()) {
		cout << "Yes" << '\n';
		for (int i = 1; i <= n; i++) cout << res[i] << ' ';
		cout << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}