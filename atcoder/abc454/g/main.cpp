#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto par, auto v) {
	vector adj(n + 1, vector(0, 0));
	vector sz(n + 1, 1);
	for (int i = n; i >= 2; i--) {
		adj[par[i]].push_back(i);
		sz[par[i]] += sz[i];
	}
	vector res(n + 1, array{ 0, 0 });
	vector cnt(n + 1, 0);
	vector freq(n + 1, 0);
	int mx = 0;
	auto push = [&](int x) {
		if (cnt[x] != 0) freq[cnt[x]]--;
		cnt[x]++;
		freq[cnt[x]]++;
		if (mx < cnt[x]) mx = cnt[x];
	};
	auto pop = [&](int x) {
		freq[cnt[x]]--;
		cnt[x]--;
		if (cnt[x] != 0) freq[cnt[x]]++;
		if (freq[mx] == 0) mx--;
	};
	auto rec = [&](const auto& self, int cur) -> void {
		int pos = -1;
		for (int nxt : adj[cur]) {
			if (pos != -1 && sz[pos] >= sz[nxt]) continue;
			pos = nxt;
		}
		for (int nxt : adj[cur]) {
			if (nxt == pos) continue;
			self(self, nxt);
			auto dfs = [&](const auto& self, int cur) -> void {
				pop(v[cur]);
				for (int nxt : adj[cur]) self(self, nxt);
			};
			dfs(dfs, nxt);
		}
		if (pos != -1) {
			self(self, pos);
		}
		for (int nxt : adj[cur]) {
			if (nxt == pos) continue;
			auto dfs = [&](const auto& self, int cur) -> void {
				push(v[cur]);
				for (int nxt : adj[cur]) self(self, nxt);
			};
			dfs(dfs, nxt);
		}
		push(v[cur]);
		res[cur][0] = mx;
		res[cur][1] = freq[mx];
	};
	rec(rec, 1);
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int a = res[i][0] ^ i;
		int b = res[i][1] ^ i;
		ret += i64(a) * b % 998'244'353;
		if (ret >= 998'244'353) ret -= 998'244'353;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k, seed; cin >> n >> seed >> m >> k;
	vector par(n + 1, 0);
	vector v(n + 1, 0);
	for (int i = 2; i <= m; i++) cin >> par[i];
	for (int i = m + 1; i <= n; i++) {
		par[i] = seed % (i - 1) + 1;
		seed = (i64(seed) * 1'103'515'245 + 12'345) & ((i64(1) << 31) - 1);
	}
	for (int i = 1; i <= m; i++) cin >> v[i];
	for (int i = m + 1; i <= n; i++) {
		v[i] = seed % k + 1;
		seed = (i64(seed) * 1'103'515'245 + 12'345) & ((i64(1) << 31) - 1);
	}
	cout << sol(n, par, v) << '\n';
}