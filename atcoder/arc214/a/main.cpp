#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	for (int iter = 0; iter <= 2 * n - 2; iter++) {
		int val = -1;
		for (int i = 0; i < n; i++) {
			int j = iter - i;
			if (j < 0 || j >= n) continue;
			if (v[i][j] == '?') continue;
			if (val == -1) val = v[i][j] - 48;
			if (val != v[i][j] - 48) return vector(0, string{});
		}
		if (val == -1) val = 0;
		for (int i = 0; i < n; i++) {
			int j = iter - i;
			if (j < 0 || j >= n) continue;
			v[i][j] = val + 48;
		}
	}
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	if (res.size()) {
		for (int i = 0; i < n; i++) cout << res[i] << '\n';
	}
	else {
		cout << -1 << '\n';
	}
}