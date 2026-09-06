#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector c(n + 1, array{ i64(0), i64(0) });
	i64 lo = *max_element(v.begin() + 1, v.end());
	i64 hi = 2 * lo;
	i64 sa = 0;
	i64 sb = 0;
	for (int i = n; i >= 1; i--) {
		auto& [a, b] = c[i];
		a = 1;
		b = -v[i];
		for (int j = 2 * i; j <= n; j += i) {
			a -= c[j][0];
			b -= c[j][1];
		}
		if (a <= 0 && b < 0) return i64(-1);
		if (a > 0) lo = max(lo, (a - b - 1) / a);
		if (a < 0) hi = min(hi, b / (-a));
		if (lo > hi) return i64(-1);
		sa += a;
		sb += b;
	}
	return sa * lo + sb;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}