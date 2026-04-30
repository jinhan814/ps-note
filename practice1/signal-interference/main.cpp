#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using f64 = double;

auto sol = [](int n, int m, auto v) {
	sort(v.begin(), v.end());
	auto check = [&](f64 mid) {
		f64 len = f64(m) / n;
		f64 mn = 0, mx = len;
		for (int i = 0; i < n; i++) {
			f64 l = i * len;
			f64 r = (i + 1) * len;
			f64 a = max(v[i] - mid, l);
			f64 b = min(v[i] + mid, r);
			if (r < a || b < l) return false;
			if (i % 2 == 0) {
				mn = max(mn, a - l);
				mx = min(mx, b - l);
			}
			else {
				mn = max(mn, r - b);
				mx = min(mx, r - a);
			}
		}
		return mn <= mx;
	};
	f64 lo = 0, hi = m;
	for (int iter = 0; iter < 100; iter++) {
		f64 mid = (lo + hi) / 2;
		if (!check(mid)) lo = mid;
		else hi = mid;
	}
	return hi;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> m >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		char c; cin >> c;
	}
	cout << fixed << setprecision(20);
	cout << sol(n, m, v) << '\n';
}