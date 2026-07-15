#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	sort(v.begin(), v.end());
	v.push_back(2'000'000'001);
	auto calc = [&](int a, int b) {
		int p = lower_bound(v.begin(), v.end(), a) - v.begin();
		int lo = p - 1, hi = n;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if ((v[mid] - a) - (mid - p) < b) lo = mid;
			else hi = mid;
		}
		int cnt = (v[hi] - a) - (hi - p);
		return (v[hi] - 1) - (cnt - b);
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