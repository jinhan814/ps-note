#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, string s, auto qs) {
	vector cnt(15, vector(15, 0));
	for (int i = 1; i < n; i++) {
		int a = s[i - 1] - 'A';
		int b = s[i] - 'A';
		cnt[a][b]++;
	}
	vector c(1 << 15, i64(0));
	for (int mask = 0; mask < 1 << 15; mask++) {
		for (int i = 0; i < 15; i++) {
			if (~mask >> i & 1) continue;
			for (int j = 0; j < 15; j++) {
				if (mask >> j & 1) continue;
				c[mask] += cnt[i][j];
			}
		}
	}
	vector val(29, i64(1) << 60);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (s[0] == s[n - 1] && i != j) continue;
			if (s[0] != s[n - 1] && i == j) continue;
			vector dp(1 << 15, i64(-1));
			auto rec = [&](const auto& self, int mask) -> i64 {
				if (mask == (1 << 15) - 1) return 0;
				i64& ret = dp[mask];
				if (ret != -1) return ret;
				ret = i64(1) << 60;
				int pc = __builtin_popcount(mask);
				for (int k = 0; k < 15; k++) {
					if (mask >> k & 1) continue;
					if (k == s[0] - 'A' && pc != i) continue;
					if (k == s[n - 1] - 'A' && pc != j) continue;
					ret = min(ret, self(self, mask | 1 << k));
				}
				ret += c[mask];
				return ret;
			};
			i64 res = rec(rec, 0);
			val[j - i + 14] = min(val[j - i + 14], res);
		}
	}
	auto calc = [&](i64 l, i64 r) {
		if (s[0] == s[n - 1]) return val[14] * (l + r);
		i64 ret = i64(1) << 60;
		for (int i = 1; i <= 14; i++) {
			ret = min(ret, val[14 + i] * (l + r) - i * l);
			ret = min(ret, val[14 - i] * (l + r) + i * l);
		}
		return ret;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [a, b, c] = qs[i];
		ret[i] = n * a + calc(b, c);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	int q; cin >> q;
	vector qs(q, array{ i64(0), i64(0), i64(0) });
	for (auto& [a, b, c] : qs) cin >> a >> b >> c;
	auto res = sol(n, q, s, qs);
	for (i64 x : res) cout << x << '\n';
}