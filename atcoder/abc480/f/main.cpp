#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 val = 0;
	for (int i = 0; i < n; i++) val += v[i];
	val /= m;
	vector dp(1 << n, -1);
	auto rec = [&](const auto& self, int mask) -> int {
		if (mask == 0) return 0;
		int& ret = dp[mask];
		if (ret != -1) return ret;
		ret = 0;
		i64 acc = 0;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) acc += v[i];
			else ret = max(ret, self(self, mask ^ 1 << i));
		}
		if (acc % val == 0) ret++;
		return ret;
	};
	return m - rec(rec, (1 << n) - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}