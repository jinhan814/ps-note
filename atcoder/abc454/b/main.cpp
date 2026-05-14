#include <bits/stdc++.h>
using namespace std;

auto sol_1 = [](int n, int m, auto v) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[i] == v[j]) return false;
		}
	}
	return true;
};

auto sol_2 = [](int n, int m, auto v) {
	vector c(m + 1, false);
	for (int i = 0; i < n; i++) {
		c[v[i]] = true;
	}
	for (int i = 1; i <= m; i++) {
		if (c[i]) continue;
		return false;
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol_1(n, m, v) ? "Yes" : "No") << '\n';
	cout << (sol_2(n, m, v) ? "Yes" : "No") << '\n';
}