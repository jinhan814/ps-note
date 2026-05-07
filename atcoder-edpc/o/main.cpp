#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1'000'000'007;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, auto v) {
	vector dp(1 << n, -1);
	auto rec = [&](const auto& self, int i, int mask) -> int {
		if (i == n) return 1;
		int& ret = dp[mask];
		if (ret != -1) return ret;
		ret = 0;
		for (int j = 0; j < n; j++) {
			if (mask >> j & 1) continue;
			if (!v[i][j]) continue;
			ret = add(ret, self(self, i + 1, mask | 1 << j));
		}
		return ret;
	};
	return rec(rec, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	cout << sol(n, v) << '\n';
}