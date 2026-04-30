#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b, auto v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	if (v.size() <= a + b) return 1;
	int lo = 0, hi = 1 << 30;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		vector pa(v.size(), 0);
		vector pb(v.size(), 0);
		for (int i = 0, j = 0, k = 0; i < v.size(); i++) {
			while (j < v.size() && v[j] - v[i] + 1 <= mid) j++;
			while (k < v.size() && v[k] - v[i] + 1 <= 2 * mid) k++;
			pa[i] = j;
			pb[i] = k;
		}
		vector dp(a + 1, vector(b + 1, -1));
		auto rec = [&](const auto& self, int x, int y) -> int {
			int& ret = dp[x][y];
			if (ret != -1) return ret;
			ret = 0;
			if (x > 0) {
				int res = self(self, x - 1, y);
				if (res == v.size()) return ret = v.size();
				ret = max(ret, pa[res]);
			}
			if (y > 0) {
				int res = self(self, x, y - 1);
				if (res == v.size()) return ret = v.size();
				ret = max(ret, pb[res]);
			}
			return ret;
		};
		if (rec(rec, a, b) != v.size()) lo = mid;
		else hi = mid;
	}
	return hi;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, a, b, v) << '\n';
}