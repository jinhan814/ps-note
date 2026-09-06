#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector c(n, 0);
	i64 acc = 0;
	int mn = 1 << 30;
	for (int i = 0; i < n; i++) {
		c[i] = v[i][1] - v[i][0];
		acc += v[i][0];
		mn = min(mn, v[i][0]);
	}
	sort(c.begin(), c.end());
	i64 ret = acc;
	for (int i = 1; i <= n; i++) {
		acc += c[i - 1];
		int cnt = max(2 * i - n, 0);
		ret = min(ret, acc + i64(cnt) * mn);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << sol(n, v) << '\n';
	}
}