#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128;
using f64 = double;

auto sol = [](int n, int q, auto v, auto qs) {
	auto f = [&](int a, int b, int c) {
		i64 v1 = i64(v[b][0] - v[a][0]) * (v[c][1] - v[a][1]);
		i64 v2 = i64(v[b][1] - v[a][1]) * (v[c][0] - v[a][0]);
		i64 x = v[a][0] + v[b][0] + v[c][0];
		i64 y = v[a][1] + v[b][1] + v[c][1];
		return tuple(x * (v1 - v2), y * (v1 - v2), v1 - v2);
	};
	auto add = [&](auto a, auto b) {
		auto [x1, y1, v1] = a;
		auto [x2, y2, v2] = b;
		return tuple(x1 + x2, y1 + y2, v1 + v2);
	};
	auto sub = [&](auto a, auto b) {
		auto [x1, y1, v1] = a;
		auto [x2, y2, v2] = b;
		return tuple(x1 - x2, y1 - y2, v1 - v2);
	};
	vector psum(n + 1, tuple(i128(0), i128(0), i64(0)));
	for (int i = 3; i <= n; i++) psum[i] = add(psum[i - 1], f(1, i - 1, i));
	auto calc = [&](int a, int b) {
		bool flag = a > b;
		if (flag) swap(a, b);
		auto res = sub(sub(psum[b], psum[a]), f(1, a, b));
		if (flag) res = sub(psum[n], res);
		auto [x, y, val] = res;
		return pair(f64(x) / (3 * val), f64(y) / (3 * val));
	};
	vector ret(q, pair(f64(0), f64(0)));
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		ret[i] = calc(a, b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, array{ 0, 0 });
	vector qs(q, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	cout << fixed << setprecision(20);
	for (auto& [a, b] : res) cout << a << ' ' << b << '\n';
}