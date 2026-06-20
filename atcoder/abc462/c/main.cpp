#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int ret = 0, mn = 1 << 30;
	for (int i = 1; i <= n; i++) {
		mn = min(mn, v[i]);
		if (mn == v[i]) ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		v[a] = b;
	}
	cout << sol(n, v) << '\n';
}