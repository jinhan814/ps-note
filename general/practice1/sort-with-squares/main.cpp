#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

auto sol = [](int n, auto v) {
	auto c = v;
	sort(c.begin(), c.end());
	for (int i = 0; i < n; i++) {
		i128 x = i128(v[i]) * c[i];
		i128 lo = 0, hi = 1LL << 60;
		while (lo + 1 < hi) {
			i128 mid = (lo + hi) / 2;
			if (mid * mid <= x) lo = mid;
			else hi = mid;
		}
		if (lo * lo != x) return 0;
	}
	return 1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0LL);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, v) ? "YES" : "NO") << '\n';
}