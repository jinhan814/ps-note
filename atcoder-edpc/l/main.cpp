#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector dp(n, vector(n, i64(1) << 60));
	auto rec = [&](const auto& self, int l, int r) -> i64 {
		if (l == r) return v[l];
		i64& ret = dp[l][r];
		if (ret != i64(1) << 60) return ret;
		ret = -(i64(1) << 60);
		ret = max(ret, v[l] - self(self, l + 1, r));
		ret = max(ret, v[r] - self(self, l, r - 1));
		return ret;
	};
	return rec(rec, 0, n - 1);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}