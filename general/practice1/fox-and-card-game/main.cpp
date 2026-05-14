#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int v1 = 0, v2 = 0;
	vector c(0, 0);
	for (int i = 0; i < n; i++) {
		int sz = v[i].size();
		for (int j = 0; j < sz / 2; j++) {
			v1 += v[i][j];
			v2 += v[i][sz - 1 - j];
		}
		if (sz % 2 == 1) c.push_back(v[i][sz / 2]);
	}
	sort(c.begin(), c.end(), greater{});
	for (int i = 0; i < c.size(); i++) {
		if (i % 2 == 0) v1 += c[i];
		else v2 += c[i];
	}
	return pair(v1, v2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(0, 0));
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		v[i].resize(k);
		for (int& x : v[i]) cin >> x;
	}
	auto [a, b] = sol(n, v);
	cout << a << ' ' << b << '\n';
}