#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto ccw = [](auto a, auto b, auto c) {
	i64 x1 = b[0] - a[0], y1 = b[1] - a[1];
	i64 x2 = c[0] - b[0], y2 = c[1] - b[1];
	i64 res = x1 * y2 - x2 * y1;
	return res ? res > 0 ? 1 : -1 : 0;
};

auto sol = [](int n, auto v) {
	vector ret(n - 2, 0);
	for (int iter = 0; iter < 2; iter++) {
		for (int i = 0; i < n; i++) {
			auto c = v;
			c.erase(c.begin() + i);
			sort(c.begin(), c.end(), [&](auto a, auto b) {
				if ((a > v[i]) != (b > v[i])) return a > v[i];
				return ccw(a, v[i], b) < 0;
			});
			for (int p = 0, a = 0, b = 0; p < c.size(); p++) {
				array u{ v[i][0] - (c[p][1] - v[i][1]), v[i][1] + (c[p][0] - v[i][0]) };
				if (b < p) b = p;
				while (b + 1 < p + c.size() && ccw(c[p], v[i], c[(b + 1) % c.size()]) < 0) b++;
				if (a < p) a = p;
				while (a + 1 <= b && ccw(u, v[i], c[(a + 1) % c.size()]) > 0) a++;
				if (a != p) ret[a - p - 1]--;
				if (b != p) ret[b - p - 1]++;
			}
		}
		for (int i = 0; i < n; i++) v[i][0] = -v[i][0];
	}
	for (int i = n - 4; i >= 0; i--) ret[i] += ret[i + 1];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	auto res = sol(n, v);
	for (int i = 0; i <= n - 3; i++) cout << res[i] << '\n';
}