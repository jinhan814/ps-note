#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 100'000;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int m, auto v) {
	int sz = 1 << m;
	vector dp(sz + 1, 0); dp[0] = 1;
	vector ndp(sz + 1, 0);
	vector q(1, 0);
	vector nq(0, 0);
	vector c(sz + 1, false);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			auto update = [&](int i, int x) {
				if (x == 0) return;
				ndp[i] = add(ndp[i], x);
				if (i == sz || c[i]) return;
				nq.push_back(i);
				c[i] = true;
			};
			if (v[i][j] == 'J' || v[i][j] == '?') {
				for (int s : q) {
					int ns = (s << 1) & (sz - 1);
					if (s & 1) ns ^= 2;
					if (j + 1 < m) ns ^= 1;
					update(ns, dp[s]);
				}
				update(sz, dp[sz]);
			}
			if (v[i][j] == 'O' || v[i][j] == '?') {
				for (int s : q) {
					int ns = (s << 1) & (sz - 1);
					update(ns, dp[s]);
				}
				update(sz, dp[sz]);
			}
			if (v[i][j] == 'I' || v[i][j] == '?') {
				for (int s : q) {
					int ns = (s << 1) & (sz - 1);
					if (s & 1) ns ^= 2;
					if (s >> (m - 1) & 1) ns = sz;
					update(ns, dp[s]);
				}
				update(sz, dp[sz]);
			}
			for (int s : q) dp[s] = 0;
			dp[sz] = 0;
			for (int s : nq) c[s] = false;
			q.clear();
			dp.swap(ndp);
			q.swap(nq);
		}
	}
	return dp[sz];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}