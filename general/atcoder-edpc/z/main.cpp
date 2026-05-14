#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 k, auto v) {
	vector dp(n, i64(0));
	deque dq(1, pair(i64(-2) * v[0], dp[0] + i64(v[0]) * v[0]));
	for (int i = 1; i < n; i++) {
		while (dq.size() >= 2) {
			i64 v1 = dq[0].first * v[i] + dq[0].second;
			i64 v2 = dq[1].first * v[i] + dq[1].second;
			if (v1 < v2) break;
			dq.pop_front();
		}
		dp[i] = dq[0].first * v[i] + dq[0].second + i64(v[i]) * v[i] + k;
		i64 a = i64(-2) * v[i];
		i64 b = dp[i] + i64(v[i]) * v[i];
		while (dq.size() >= 2) {
			auto [a1, b1] = dq[dq.size() - 2];
			auto [a2, b2] = dq.back();
			if ((b2 - b1) * (a2 - a) < (b - b2) * (a1 - a2)) break;
			dq.pop_back();
		}
		dq.push_back(pair(a, b));
	}
	return dp[n - 1];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}