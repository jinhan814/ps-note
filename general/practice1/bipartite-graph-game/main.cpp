#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector c1(n, 0), c2(m, 0);
	for (int i = 0; i < k; i++) {
		c1[v[i][0] - 1]++;
		c2[v[i][1] - 1]++;
	}
	auto d1 = c1, d2 = c2;
	sort(d1.begin(), d1.end());
	sort(d2.begin(), d2.end());
	int acc = 0;
	for (int i = 0; i < n; i++) acc += d1[i] * (i + 1);
	for (int i = 0; i < m; i++) acc += d2[i] * (i + 1);
	int opt = 1 << 30;
	for (int i = 0; i < k; i++) {
		int a = lower_bound(d1.begin(), d1.end(), c1[v[i][0] - 1]) - d1.begin() + 1;
		int b = lower_bound(d2.begin(), d2.end(), c2[v[i][1] - 1]) - d2.begin() + 1;
		opt = min(opt, a + b);
	}
	return pair(acc, acc - opt);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m, k; cin >> n >> m >> k;
		vector v(k, array{ 0, 0 });
		for (int i = 0; i < k; i++) cin >> v[i][0] >> v[i][1];
		auto [a, b] = sol(n, m, k, v);
		cout << a << ' ' << b << '\n';
	}
}