#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int mul(int a, int b) {
	return i64(a) * b % mod;
}

constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

auto sol = [](int n, int m, string s, auto v) {
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	vector adj(n, vector(0, 0));
	for (auto [a, b] : v) {
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}
	int ret = 1;
	bool flag = true;
	vector c(n, false);
	for (int i = 0; i < n; i++) {
		if (c[i]) continue;
		if (adj[i].empty()) continue;
		int sz = 0;
		vector cnt(26, 0);
		auto rec = [&](const auto& self, int cur) -> void {
			c[cur] = true;
			sz++;
			cnt[s[cur] - 'a']++;
			for (int nxt : adj[cur]) {
				if (c[nxt]) continue;
				c[nxt] = true;
				self(self, nxt);
			}
		};
		rec(rec, i);
		ret = mul(ret, fac[sz]);
		for (int i = 0; i < 26; i++) {
			if (cnt[i] >= 2) flag = false;
			ret = mul(ret, inv[cnt[i]]);
		}
	}
	if (flag) ret = mul(ret, inv[2]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;
	vector v(m, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, m, s, v) << '\n';
}