#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto sol = [](int n, auto v) {
	i64 r1 = i64(1) << 60, r2 = 1;
	for (int iter = 0; iter < 2; iter++) {
		vector c(0, array{ 0, 0 });
		i64 acc = 0;
		for (auto [a, b] : v) {
			if (b == 0) continue;
			if (b < 0) a = -a, b = -b;
			c.push_back(array{ a, b });
			acc += b;
		}
		if (c.empty()) continue;
		sort(c.begin(), c.end(), [](auto a, auto b) {
			i64 v1 = i64(a[0]) * b[1];
			i64 v2 = i64(b[0]) * a[1];
			return v1 < v2;
		});
		int p = 0;
		while (p + 1 < c.size() && acc - 2 * c[p][1] > 0) {
			acc -= 2 * c[p][1];
			p++;
		}
		i64 res = 0;
		for (int i = 0; i < n; i++) {
			i64 v1 = i64(c[p][0]) * v[i][1];
			i64 v2 = i64(c[p][1]) * v[i][0];
			res += abs(v1 - v2);
			swap(v[i][0], v[i][1]);
		}
		if (i128(r1) * c[p][1] > i128(r2) * res) {
			r1 = res;
			r2 = c[p][1];
		}
	}
	if (r1 == i64(1) << 60) r1 = 0;
	i64 g = gcd(r1, r2);
	return pair(r1 / g, r2 / g);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0];
	for (int i = 0; i < n; i++) cin >> v[i][1];
	auto [a, b] = sol(n, v);
	cout << a << ' ' << b << '\n';
}