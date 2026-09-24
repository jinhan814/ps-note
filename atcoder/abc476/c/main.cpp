#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(0, 0);
	vector c{ v[0], v[1] };
	for (int i = 2; i < n; i++) {
		c.push_back(v[i]);
		sort(c.begin(), c.end(), greater{});
		if (c.size() > 3) c.pop_back();
		ret.push_back(c[2]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int x : res) cout << x << '\n';
}