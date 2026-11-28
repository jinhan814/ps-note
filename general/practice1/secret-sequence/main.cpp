#include <bits/stdc++.h>
using namespace std;

int main() {
	map cache{ pair(tuple(0, 0, 0, 0), 0) };
	cache.clear();
	auto ask = [&](int a, int b, int c, int d) {
		if (cache.count(tuple(a, b, c, d))) return cache[tuple(a, b, c, d)];
		cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
		int x; cin >> x;
		return cache[tuple(a, b, c, d)] = x;
	};
	auto rec = [&](const auto& self, int l, int r) {
		if (r - l <= 0) return 0;
		if (r - l == 1) return ask(0, 0, l, r);
		int lo = l, hi = r;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (ask(l, mid, mid, r) >= 0) lo = mid;
			else hi = mid;
		}
		if (ask(l, lo, lo, r) > 0) {
			int nl = l, nr = lo;
			if (lo - l > r - hi) nl = hi, nr = r;
			return 2 * self(self, nl, nr) + 1;
		}
		else {
			int nl = l, nr = lo;
			if (lo - l > r - lo) nl = lo, nr = r;
			return 2 * self(self, nl, nr);
		}
	};
	int n; cin >> n;
	int res = rec(rec, 0, n);
	cout << "! " << res << endl;
}