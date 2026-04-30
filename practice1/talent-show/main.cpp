#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int a, int b, auto v) {
	int lo = 1'000 * b / a, hi = 1'000'001;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		i64 acc = 0;
		for (int i = 0; i < v.size(); i++) {
			i64 val = i64(1'000) * v[i][1] - i64(mid) * v[i][0];
			if (val > 0) acc += val;
		}
		if (acc >= i64(mid) * a - i64(1'000) * b) lo = mid;
		else hi = mid;
	}
	return lo;
};

auto sol = [](int n, int m, auto v) {
	vector buc(2, vector(0, array{ 0, 0 }));
	for (int i = 0; i < n; i++) {
		if (v[i][0] < m) buc[0].push_back(v[i]);
		else buc[1].push_back(v[i]);
	}
	vector dp(n * (m - 1) + 1, -1);
	dp[0] = 0;
	for (auto [a, b] : buc[0]) {
		for (int i = n * (m - 1) - a; i >= 0; i--) {
			if (dp[i] == -1) continue;
			dp[i + a] = max(dp[i + a], dp[i] + b);
		}
	}
	int ret = 0;
	for (int i = m; i <= n * (m - 1); i++) {
		if (dp[i] == -1) continue;
		ret = max(ret, 1'000 * dp[i] / i);
	}
	for (auto [a, b] : buc[1]) {
		int res = calc(a, b, buc[0]);
		ret = max(ret, res);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, m, v) << '\n';
}