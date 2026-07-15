#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	sort(v.begin(), v.end());
	auto f = [&](int l, int r) {
		int p1 = lower_bound(v.begin(), v.end(), l) - v.begin();
		int p2 = upper_bound(v.begin(), v.end(), r) - v.begin();
		return p2 - p1;
	};
	auto calc = [&](int a, int b) {
		int lo = a - 1, hi = 2'000'000'000;
		while (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			if ((mid - a + 1) - f(a, mid) < b) lo = mid;
			else hi = mid;
		}
		return hi;
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		ret[i] = calc(a, b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i];
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}