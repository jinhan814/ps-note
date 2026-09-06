#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector c{ 1, n + 1 };
	for (auto [a, b] : qs) {
		c.push_back(a);
		c.push_back(b + 1);
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector ret(q, 0);
	int acc = n;
	set s(c.begin(), c.end() - 1);
	for (int i = 0; i < q; i++) {
		auto [a, b] = qs[i];
		auto it = s.lower_bound(a);
		while (it != s.end() && *it <= b) {
			int p = lower_bound(c.begin(), c.end(), *it) - c.begin();
			acc -= c[p + 1] - c[p];
			it = s.erase(it);
		}
		ret[i] = acc;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0 });
	for (auto& [a, b] : qs) cin >> a >> b;
	auto res = sol(n, q, qs);
	for (int x : res) cout << x << '\n';
}