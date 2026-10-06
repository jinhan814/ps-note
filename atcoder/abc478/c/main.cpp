#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int p1 = -1, mx = 0;
	for (int i = 0; i < n; i++) {
		if (mx < v[i]) mx = v[i];
		if (mx > v[i]) p1 = i;
	}
	int p2 = n, mn = 1 << 30;
	for (int i = n - 1; i >= 0; i--) {
		if (mn > v[i]) mn = v[i];
		if (mn < v[i]) p2 = i;
	}
	return p1 - p2 + 1 <= m;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, m, v) ? "Yes" : "No") << '\n';
}