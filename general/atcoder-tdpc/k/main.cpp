#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		if (a[0] - a[1] != b[0] - b[1]) return a[0] - a[1] < b[0] - b[1];
		return a[0] + a[1] < b[0] + b[1];
	});
	vector c(0, 0);
	for (int i = 0; i < n; i++) {
		int val = -(v[i][0] + v[i][1]);
		auto it = lower_bound(c.begin(), c.end(), val);
		if (it == c.end()) c.push_back(val);
		else *it = val;
	}
	return c.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}