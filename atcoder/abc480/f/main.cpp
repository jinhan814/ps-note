#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector acc(1 << n, i64(0));
	for (int i = 0; i < n; i++) acc[1 << i] += v[i];
	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < 1 << n; mask++) {
			if (~mask >> i & 1) continue;
			acc[mask] += acc[mask ^ 1 << i];
		}
	}
	i64 val = acc.back() / m;
	vector dp(1 << n, -1);
	auto rec = [&](const auto& self, int mask) -> int {
		if (mask == 0) return 0;
		int& ret = dp[mask];
		if (ret != -1) return ret;
		ret = 1 << 30;
		i64 x = (acc.back() - acc[mask]) % val;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			int v1 = self(self, mask ^ 1 << i);
			int v2 = (v[i] + x - 1) / val;
			ret = min(ret, v1 + v2);
		}
		return ret;
	};
	return rec(rec, (1 << n) - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}