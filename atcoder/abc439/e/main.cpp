#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		if (a[0] != b[0]) return a[0] < b[0];
		return a[1] > b[1];
	});
	vector c(0, 0);
	for (int i = 0; i < n; i++) {
		if (c.empty() || c.back() < v[i][1]) c.push_back(v[i][1]);
		else *lower_bound(c.begin(), c.end(), v[i][1]) = v[i][1];
	}
	return c.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	cout << sol(n, v) << '\n';
}