#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto a, auto b) {
	vector c(1, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) c.push_back(array{ a[i][0], a[i][1], 0 });
	for (int i = 0; i < m; i++) c.push_back(array{ b[i][0], b[i][1], 1 });
	sort(c.begin(), c.end());
	map buc{ pair(0, vector(0, 0)) };
	for (int i = 0; i < c.size(); i++) {
		int v1 = (c[i][0] - c[i][1]) % (2 * k);
		int v2 = (c[i][0] + c[i][1]) % (2 * k);
		if (v1 < 0) v1 += 2 * k;
		buc[v1].push_back(i);
		if (v1 != v2) buc[v2].push_back(i);
	}
	vector dp(c.size(), array{ -1, -1 });
	auto rec = [&](const auto& self, int i, int f) -> int {
		int& ret = dp[i][f];
		if (ret != -1) return ret;
		int pos = (c[i][0] + c[i][1] * (f == 0 ? -1 : 1)) % (2 * k);
		if (pos < 0) pos += 2 * k;
		auto& cand = buc[pos];
		if (cand.back() == i) return ret = 0;
		int lo = 0, hi = cand.size() - 1;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (c[cand[mid]][0] <= c[i][0]) lo = mid;
			else hi = mid;
		}
		int ni = cand[hi];
		if (c[ni][2] == 0) {
			int v1 = self(self, ni, 0);
			int v2 = self(self, ni, 1);
			return ret = max(v1, v2);
		}
		else {
			int val = (c[ni][0] - pos) % (2 * k);
			if (val < 0) val += 2 * k;
			int nf = val < k ? 0 : 1;
			return ret = self(self, ni, nf) + 1;
		}
	};
	return rec(rec, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int k; cin >> k;
		int n; cin >> n;
		vector a(n, array{ 0, 0 });
		for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
		int m; cin >> m;
		vector b(m, array{ 0, 0 });
		for (int i = 0; i < m; i++) cin >> b[i][0] >> b[i][1];
		cout << sol(n, m, k, a, b) << '\n';
	}
}