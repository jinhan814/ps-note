#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 k, auto v) {
	i64 lo = 0, hi = i64(1) << 61;
	while (lo + 1 < hi) {
		i64 mid = (lo + hi) / 2;
		i64 cnt = 0;
		for (int i = 0; i < n; i++) {
			if (v[i] >= mid) continue;
			cnt += (mid - v[i] + i) / (i + 1);
			if (cnt > k) break;
		}
		if (cnt <= k) lo = mid;
		else hi = mid;
	}
	return lo;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 k; cin >> k;
	vector v(n, i64(0));
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}