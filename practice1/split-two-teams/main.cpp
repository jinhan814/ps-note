#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector buc(101, vector(0, 0));
	int mn = 1 << 30, acc = 0;
	for (auto [a, b] : v) {
		buc[a].push_back(b);
		mn = min(mn, a);
		acc += b;
	}
	bitset<100'001> dp;
	dp[0] = 1;
	int ret = 1 << 30, sz = 0;
	for (int i = 100; i >= mn; i--) {
		if (buc[i].empty()) continue;
		bitset<100'001> c;
		for (int j = 0; j < buc[i].size(); j++) {
			if (i == mn && j == 0) continue;
			int x = buc[i][j];
			c |= dp << x;
			dp |= dp << x;
			sz += x;
		}
		for (int x = 1; x <= sz; x++) {
			if (!c[x]) continue;
			int v1 = i * x;
			int v2 = mn * (acc - x);
			ret = min(ret, abs(v1 - v2));
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}