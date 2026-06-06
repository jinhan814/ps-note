#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	vector dep(n + 1, -1);
	vector buc(0, pair(0, 0));
	auto rec = [&](const auto& self, int cur) -> void {
		for (int nxt : adj[cur]) {
			if (dep[nxt] == -1) {
				dep[nxt] = dep[cur] + 1;
				self(self, nxt);
			}
			if (dep[nxt] < dep[cur] - 1) {
				buc.push_back(pair(cur, nxt));
			}
		}
	};
	dep[1] = 0;
	rec(rec, 1);
	int ret = 0;
	for (int mask = 0; mask < 1 << buc.size(); mask++) {
		vector c(n + 1, -1);
		bool flag = true;
		for (int i = 0; i < buc.size(); i++) {
			auto [a, b] = buc[i];
			if (c[a] == -1) c[a] = mask >> i & 1;
			if (c[a] != (mask >> i & 1)) flag = false;
		}
		for (int i = 0; i < buc.size(); i++) {
			auto [a, b] = buc[i];
			if (c[a] == 1 && c[b] == 1) flag = false;
			else if (c[a] == 1) c[b] = 0;
			else if (c[b] == 1) c[a] = 0;
		}
		if (!flag) continue;
		vector dp(n + 1, array{ -1, -1 });
		auto rec = [&](const auto& self, int cur, int f) -> int {
			if (c[cur] != -1 && c[cur] != f) return -(1 << 30);
			int& ret = dp[cur][f];
			if (ret != -1) return ret;
			ret = f;
			for (int nxt : adj[cur]) {
				if (dep[nxt] != dep[cur] + 1) continue;
				int v1 = self(self, nxt, 0);
				int v2 = self(self, nxt, 1);
				if (f == 0 && v1 < v2) swap(v1, v2);
				if (v1 == -(1 << 30)) return -(1 << 30);
				ret += v1;
			}
			return ret;
		};
		ret = max(ret, rec(rec, 1, 0));
		ret = max(ret, rec(rec, 1, 1));
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