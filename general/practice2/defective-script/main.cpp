#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector d(n, i64(0));
	d[0] = v[0] - v[n - 1];
	for (int i = 1; i < n; i++) d[i] = v[i] - v[i - 1];
	i64 cnt = 0;
	for (int iter = 0; iter < 40; iter++) {
		for (int i = n - 1; i >= 0; i--) {
			if (d[i] >= 0) continue;
			i64 val = (-d[i] + 1) / 2;
			cnt += val;
			d[i] += 2 * val;
			d[(i - 1 + n) % n] -= val;
			d[(i - 2 + n) % n] -= val;
		}
	}
	i64 acc = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] != 0) return 0;
		acc += v[i];
	}
	if (acc < 3 * cnt) return 0;
	return int((acc - 3 * cnt) / n);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, i64(0));
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}