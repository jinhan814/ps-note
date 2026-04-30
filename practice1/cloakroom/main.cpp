#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector c(0, 0);
	for (int i = 0; i < n; i++) c.push_back(v[i][0]);
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector cand(c.size(), vector(0, 0));
	vector buc(c.size(), vector(0, 0));
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(c.begin(), c.end(), v[i][0]);
		cand[it - c.begin()].push_back(i);
	}
	for (int i = 0; i < q; i++) {
		if (qs[i][0] < c[0]) continue;
		auto it = prev(upper_bound(c.begin(), c.end(), qs[i][0]));
		buc[it - c.begin()].push_back(i);
	}
	vector ret(q, false);
	vector dp(100'001, -1);
	dp[0] = 1 << 30;
	for (int iter = 0; iter < c.size(); iter++) {
		for (int i : cand[iter]) {
			int a = v[i][1];
			int b = v[i][2];
			for (int x = 100'000; x >= b; x--) {
				dp[x] = max(dp[x], min(dp[x - b], a));
			}
		}
		for (int i : buc[iter]) {
			int a = qs[i][1];
			int b = qs[i][2];
			ret[i] = a <= dp[b];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) {
		cin >> v[i][2] >> v[i][0] >> v[i][1];
	}
	int q; cin >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 0; i < q; i++) {
		cin >> qs[i][0] >> qs[i][2] >> qs[i][1];
		qs[i][1] += qs[i][0] + 1;
	}
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) {
		cout << (res[i] ? "TAK" : "NIE") << '\n';
	}
}