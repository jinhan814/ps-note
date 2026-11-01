#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector c1(0, 0);
	vector c2(0, 0);
	for (auto [a, b] : v) {
		c1.push_back(a);
		c2.push_back(b);
	}
	sort(c1.begin(), c1.end());
	sort(c2.begin(), c2.end());
	c1.erase(unique(c1.begin(), c1.end()), c1.end());
	c2.erase(unique(c2.begin(), c2.end()), c2.end());
	vector p1(c1.size() + 1, 0);
	vector p2(c2.size() + 1, 0);
	for (auto [a, b] : v) {
		a = lower_bound(c1.begin(), c1.end(), a) - c1.begin();
		b = lower_bound(c2.begin(), c2.end(), b) - c2.begin();
		p1[a + 1]++;
		p2[b + 1]++;
	}
	for (int i = 1; i <= c1.size(); i++) p1[i] += p1[i - 1];
	for (int i = 1; i <= c2.size(); i++) p2[i] += p2[i - 1];
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [op, a, b] = qs[i];
		if (op == 1) {
			a = lower_bound(c1.begin(), c1.end(), a) - c1.begin();
			b = upper_bound(c1.begin(), c1.end(), b) - c1.begin();
			ret[i] = p1[b] - p1[a];
		}
		else {
			a = lower_bound(c2.begin(), c2.end(), a) - c2.begin();
			b = upper_bound(c2.begin(), c2.end(), b) - c2.begin();
			ret[i] = p2[b] - p2[a];
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