#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int sub(int a, int b) {
	return a < b ? a - b + mod : a - b;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

auto sol = [](int n, auto v, auto adj) {
	vector sz(n, 1);
	auto rec = [&](const auto& self, int cur, int prv) -> void {
		for (auto [nxt, a, b] : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur);
			v[cur] = add(v[cur], add(mul(v[nxt], a), mul(sz[nxt], b)));
			sz[cur] += sz[nxt];
		}
	};
	rec(rec, 0, -1);
	vector ret(n, 0);
	auto dfs = [&](const auto& self, int cur, int prv) -> void {
		ret[cur] = v[cur];
		for (auto [nxt, a, b] : adj[cur]) {
			if (nxt == prv) continue;
			v[cur] = sub(v[cur], add(mul(v[nxt], a), mul(sz[nxt], b)));
			sz[cur] -= sz[nxt];
			v[nxt] = add(v[nxt], add(mul(v[cur], a), mul(sz[cur], b)));
			sz[nxt] += sz[cur];
			self(self, nxt, cur);
			sz[nxt] -= sz[cur];
			v[nxt] = sub(v[nxt], add(mul(v[cur], a), mul(sz[cur], b)));
			sz[cur] += sz[nxt];
			v[cur] = add(v[cur], add(mul(v[nxt], a), mul(sz[nxt], b)));
		}
	};
	dfs(dfs, 0, -1);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	vector adj(n, vector(0, tuple(0, 0, 0)));
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		adj[a].push_back(tuple(b, c, d));
		adj[b].push_back(tuple(a, c, d));
	}
	auto res = sol(n, v, adj);
	for (int i = 0; i < n; i++) cout << res[i] << ' ';
	cout << '\n';
}