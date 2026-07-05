#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto sol = [](int n, int k, auto v) {
	vector dp(n + 1, -(i64(1) << 60));
	dp[0] = 0;
	for (int l = 1; l <= n; l += k) {
		int r = min(l + k - 1, n);
		{
			deque dq(0, pair(i64(0), i64(0)));
			auto push = [&](int i) {
				i64 a = -2 * i;
				i64 b = dp[i] + i64(i) * (i + n);
				while (dq.size() >= 2) {
					auto [a1, b1] = dq.back();
					auto [a2, b2] = dq[dq.size() - 2];
					i128 v1 = i128(b1 - b) * (a1 - a2);
					i128 v2 = i128(b2 - b1) * (a - a1);
					if (v1 > v2) break;
					dq.pop_back();
				}
				dq.push_back(pair(a, b));
			};
			auto calc = [&](int i) {
				while (dq.size() >= 2) {
					auto [a1, b1] = dq.back();
					auto [a2, b2] = dq[dq.size() - 2];
					i64 v1 = a1 * i + b1;
					i64 v2 = a2 * i + b2;
					if (v1 > v2) break;
					dq.pop_back();
				}
				auto [a, b] = dq.back();
				return a * i + b;
			};
			for (int i = r, j = l - 1; i >= l; i--) {
				while (j >= 0 && i - j <= k) push(j--);
				dp[i] = calc(i);
			}
		}
		{
			deque dq(0, pair(i64(0), i64(0)));
			auto push = [&](int i) {
				i64 a = -2 * i;
				i64 b = dp[i] + i64(i) * (i + n);
				while (dq.size() >= 2) {
					auto [a1, b1] = dq[0];
					auto [a2, b2] = dq[1];
					i128 v1 = i128(b - b1) * (a2 - a1);
					i128 v2 = i128(b1 - b2) * (a1 - a);
					if (v1 < v2) break;
					dq.pop_front();
				}
				dq.push_front(pair(a, b));
			};
			auto calc = [&](int i) {
				while (dq.size() >= 2) {
					auto [a1, b1] = dq[0];
					auto [a2, b2] = dq[1];
					i64 v1 = a1 * i + b1;
					i64 v2 = a2 * i + b2;
					if (v1 > v2) break;
					dq.pop_front();
				}
				auto [a, b] = dq[0];
				return a * i + b;
			};
			for (int i = l; i <= r; i++) {
				if (i > l) dp[i] = max(dp[i], calc(i));
				dp[i] += 2 * v[i] + i64(i) * (i - n);
				push(i);
			}
		}
	}
	return dp[n] / 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}