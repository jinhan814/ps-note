#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 a, i64 b, i64 x, i64 y) {
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (a > b) swap(a, b), swap(x, y);
	i64 ret = a * (min(x, y) * 2);
	if (x < y) {
		i64 v1 = a * ((y - x) / 2) + b * ((y - x + 1) / 2);
		i64 v2 = (4 * a) * ((y - x) / 2);
		if ((y - x) % 2 == 1) v2 += min(3 * a, b);
		ret += min(v1, v2);
	}
	if (x > y) {
		i64 v1 = b * ((x - y) / 2) + a * ((x - y + 1) / 2);
		i64 v2 = (4 * a) * ((x - y) / 2);
		if ((x - y) % 2 == 1) v2 += a;
		ret += min(v1, v2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		i64 a, b, x, y; cin >> a >> b >> x >> y;
		cout << sol(a, b, x, y) << '\n';
	}
}