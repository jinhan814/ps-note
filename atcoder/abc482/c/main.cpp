#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector ret(q, 0);
	for (int iter = 0; iter < 2; iter++) {
		vector c(0, 0);
		for (int i = 0; i < n; i++) c.push_back(v[i][iter]);
		sort(c.begin(), c.end());
		c.erase(unique(c.begin(), c.end()), c.end());
		vector p(c.size() + 1, 0);
		for (int i = 0; i < n; i++) {
			auto it = lower_bound(c.begin(), c.end(), v[i][iter]);
			p[it - c.begin() + 1]++;
		}
		for (int i = 0; i < c.size(); i++) {
			p[i + 1] += p[i];
		}
		for (int i = 0; i < q; i++) {
			auto [op, l, r] = qs[i];
			if (op != iter + 1) continue;
			l = lower_bound(c.begin(), c.end(), l) - c.begin();
			r = upper_bound(c.begin(), c.end(), r) - c.begin();
			ret[i] = p[r] - p[l];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> n >> n >> q;
	vector v(n, array{ 0, 0 });
	vector qs(q, array{ 0, 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1] >> qs[i][2];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}