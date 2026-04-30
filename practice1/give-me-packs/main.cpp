#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto adj) {
	vector in(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) in[j]++;
	}
	vector dp1(n + 1, -1), dp2(n + 1, -1);
	auto rec = [&](const auto& self, int cur, int i) -> int {
		if (i == 1) {
			if (cur == n) return 1 << 30;
			int& ret = dp1[cur];
			if (ret != -1) return ret;
			ret = 1 << 30;
			for (int nxt : adj[cur]) ret = min(ret, self(self, nxt, 2));
			return ret;
		}
		else {
			if (cur == n) return 0;
			int& ret = dp2[cur];
			if (ret != -1) return ret;
			vector buc(0, 0);
			int cnt = 0;
			for (int nxt : adj[cur]) {
				int res = self(self, nxt, 1);
				if (res != 1 << 30) buc.push_back(res);
				else cnt++;
			}
			sort(buc.begin(), buc.end(), greater{});
			ret = 1 << 30;
			for (int x : buc) ret = min(ret, cnt + x), cnt++;
			return ret;
		}
	};
	int ret = 1 << 30;
	for (int i = 1; i <= n; i++) {
		if (in[i] != 0) continue;
		ret = min(ret, rec(rec, i, 2));
	}
	if (ret == 1 << 30) return -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	cout << sol(n, m, adj) << '\n';
}