#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int ret = 0;
	vector c(0, 0);
	for (int i = 0, x = 0; i < n; i++) {
		if (x < v[i]) {
			ret++;
			x = v[i];
		}
		else {
			if (c.empty() || c.back() < v[i]) c.push_back(v[i]);
			else *lower_bound(c.begin(), c.end(), v[i]) = v[i];
		}
	}
	ret += c.size();
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}