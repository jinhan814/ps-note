#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 a, i64 b, i64 x, i64 y) {
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (a > b) swap(a, b), swap(x, y);
	i64 ret = a * (min(x, y) * 2);
	if (x < y) {
		ret += min(4 * a, a + b) * ((y - x) / 2);
		if ((y - x) % 2 == 1) ret += min(3 * a, b);
	}
	if (x > y) {
		ret += min(4 * a, a + b) * ((x - y) / 2);
		if ((x - y) % 2 == 1) ret += a;
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