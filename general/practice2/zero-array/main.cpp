#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector d(n, i64(0));
	d[0] = v[0] - v[n - 1];
	for (int i = 1; i < n; i++) d[i] = v[i] - v[i - 1];
	i64 cnt = 0;
	for (int iter = 0; iter < 2; iter++) {
		for (int i = n - 1; i >= 0; i -= 2) {
			if (d[i] >= 0) continue;
			cnt += -d[i];
			d[(i - 2 + n) % n] += d[i];
			d[i] = 0;
		}
		for (int i = n - 2; i >= 0; i -= 2) {
			if (d[i] >= 0) continue;
			cnt += -d[i];
			d[(i - 2 + n) % n] += d[i];
			d[i] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == 0) continue;
		return false;
	}
	i64 acc = 0;
	for (int i = 0; i < n; i++) acc += v[i];
	i64 val = (acc - 2 * cnt) / n;
	if (val < 0) return false;
	if (n % 2 == 1 && val % 2 == 1) return false;
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << (sol(n, v) ? "YES" : "NO") << '\n';
	}
}