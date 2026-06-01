#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int mx = *max_element(v.begin(), v.end());
	vector c(mx, 0);
	for (int i = 0; i < n; i++) {
		c[0]++;
		if (v[i] != mx) c[v[i]]--;
	}
	for (int i = 1; i < mx; i++) {
		c[i] += c[i - 1];
	}
	for (int i = 1; i < mx; i++) {
		if (c[i - 1] < 10) continue;
		c[i] += c[i - 1] / 10;
		c[i - 1] %= 10;
	}
	while (c.back() >= 10) {
		c.push_back(c.back() / 10);
		c[c.size() - 2] %= 10;
	}
	string ret(0, 0);
	for (int i = c.size() - 1; i >= 0; i--) {
		ret.push_back(c[i] + 48);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}