#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using i64 = long long;

auto sol = [](int n, int m, int k, int q, auto v, auto qs) {
	sort(v.begin(), v.end());
	auto calc = [&](int t, int x) {
		int lo = -1, hi = n;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			i64 val = i64(v[mid][0]) * m + i64(v[mid][1] - v[mid][0]) * t;
			if (val < i64(x) * m) lo = mid;
			else hi = mid;
		}
		int l = max(lo - 2 * k + 1, 0);
		int r = min(hi + 2 * k - 1, n - 1);
		i64 a = i64(1) << 60, b = 1;
		for (int i = l; i <= r; i++) {
			i64 v1 = abs(i64(v[i][0]) * m + i64(v[i][1] - v[i][0]) * t - i64(x) * m);
			i64 v2 = m;
			if (i128(a) * v2 > i128(v1) * b) a = v1, b = v2;
		}
		i64 g = gcd(a, b);
		return pair(a / g, b / g);
	};
	vector ret(q, array{ i64(0), i64(0) });
	for (int i = 0; i < q; i++) {
		auto [t, x] = qs[i];
		auto [a, b] = calc(t, x);
		ret[i][0] = a;
		ret[i][1] = b;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	int q; cin >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, m, k, q, v, qs);
	for (auto [a, b] : res) cout << a << '/' << b << '\n';
}