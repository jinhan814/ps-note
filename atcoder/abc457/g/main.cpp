#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector c(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) {
		c[i][0] = v[i][0] - v[i][1];
		c[i][1] = v[i][0] + v[i][1];
	}
	sort(c.begin(), c.end());
	vector p(0, 0);
	for (int i = 0; i < n; i++) {
		int val = -c[i][1];
		if (p.empty() || p.back() < val) p.push_back(val);
		else *lower_bound(p.begin(), p.end(), val) = val;
	}
	return p.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}