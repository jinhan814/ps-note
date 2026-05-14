#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 k, auto v, auto c) {
	for (int i = 0; i < n; i++) {
		i64 len = i64(c[i]) * i64(v[i].size());
		if (k <= len) return v[i][(k - 1) % v[i].size()];
		k -= len;
	}
	assert(0);
	return -1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector v(n, vector(0, 0));
	vector c(n, 0);
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		v[i].resize(m);
		for (int& x : v[i]) cin >> x;
	}
	for (int i = 0; i < n; i++) cin >> c[i];
	cout << sol(n, k, v, c) << '\n';
}