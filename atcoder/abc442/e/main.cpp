#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto ccw = [](auto a, auto b, auto c) {
	i64 x1 = b[0] - a[0], y1 = b[1] - a[1];
	i64 x2 = c[0] - b[0], y2 = c[1] - b[1];
	i64 res = x1 * y2 - x2 * y1;
	return res ? res > 0 ? 1 : -1 : 0;
};

auto sol = [](int n, int q, auto v, auto qs) {
	for (int i = 0; i < n; i++) {
		int g = gcd(abs(v[i][0]), abs(v[i][1]));
		v[i][0] /= g;
		v[i][1] /= g;
	}
	auto cmp = [](auto a, auto b) {
		bool f1 = a > array{ 0, 0 };
		bool f2 = b > array{ 0, 0 };
		if (f1 != f2) return f1;
		return ccw(array{ 0, 0 }, a, b) < 0;
	};
	auto c = v;
	sort(c.begin(), c.end(), cmp);
	c.erase(unique(c.begin(), c.end()), c.end());
	vector p(n, 0);
	vector psum(c.size() + 1, 0);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(c.begin(), c.end(), v[i], cmp);
		p[i] = it - c.begin() + 1;
		psum[p[i]]++;
	}
	for (int i = 1; i <= c.size(); i++) {
		psum[i] += psum[i - 1];
	}
	auto calc = [&](int a, int b) {
		if (p[a] <= p[b]) return psum[p[b]] - psum[p[a] - 1];
		return psum[p[b]] + (psum.back() - psum[p[a] - 1]);
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		ret[i] = calc(a - 1, b - 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, array{ 0, 0 });
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}