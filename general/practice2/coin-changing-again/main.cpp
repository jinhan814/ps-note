#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int q, auto v, auto qs) {
	vector dp(100'001, i64(0));
	dp[0] = 1;
	for (int i = 0; i < 4; i++) {
		for (int x = v[i]; x <= 100'000; x++) {
			dp[x] += dp[x - v[i]];
		}
	}
	auto calc = [&](int n, auto c) {
		i64 ret = 0;
		for (int mask = 0; mask < 1 << 4; mask++) {
			int x = n;
			for (int i = 0; i < 4; i++) {
				if (~mask >> i & 1) continue;
				x -= v[i] * (c[i] + 1);
			}
			if (x < 0) continue;
			ret += dp[x] * (__builtin_popcount(mask) & 1 ? -1 : 1);
		}
		return ret;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [n, c] = qs[i];
		ret[i] = calc(n, c);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		vector v(4, 0);
		for (int i = 0; i < 4; i++) cin >> v[i];
		int q; cin >> q;
		vector qs(q, tuple(0, vector(4, 0)));
		for (auto& [n, c] : qs) {
			for (int i = 0; i < 4; i++) cin >> c[i];
			cin >> n;
		}
		auto res = sol(q, v, qs);
		for (int i = 0; i < q; i++) cout << res[i] << '\n';
	}
}