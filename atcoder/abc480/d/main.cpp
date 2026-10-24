#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector p1(n + 1, i64(0));
	vector p2(n + 1, i64(0));
	for (int i = 1; i <= n; i++) {
		p1[i] = p1[i - 1] + v[i];
		p2[i] = p2[i - 1] + p1[i];
	}
	auto f = [&](i64 i) {
		int lo = 0, hi = n;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (i64(mid) * (mid + 1) / 2 < i) lo = mid;
			else hi = mid;
		}
		return hi;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [l, r] = qs[i];
		int a = f(l), b = f(r);
		l -= i64(a) * (a - 1) / 2;
		r -= i64(b) * (b - 1) / 2;
		ret[i] = p1[a] - p1[l - 1] + p1[r] + p2[b - 1] - p2[a];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, array{ i64(0), i64(0) });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}