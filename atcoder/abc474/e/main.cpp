#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		return a[0] - a[1] < b[0] - b[1];
	});
	int mn = 1 << 30;
	vector p1(n + 1, i64(0));
	vector p2(n + 1, i64(0));
	for (int i = 0; i < n; i++) {
		mn = min(mn, v[i][0]);
		p1[i + 1] = p1[i] + v[i][0];
		p2[i + 1] = p2[i] + v[i][1];
	}
	i64 ret = i64(1) << 60;
	for (int x = 1; x <= n; x++) {
		i64 val = p1[x] + (p2[n] - p2[x]);
		if (n - x > x) val += i64(n - 2 * x) * mn;
		ret = min(ret, val);
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