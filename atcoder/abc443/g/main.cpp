#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;

auto floor_sum = [](u64 n, u64 m, u64 a, u64 b) {
	u64 res = 0;
	while (1) {
		if (a >= m) res += n * (n - 1) / 2 * (a / m), a %= m;
		if (b >= m) res += n * (b / m), b %= m;
		u64 x = a * n + b;
		if (x < m) break;
		n = x / m, b = x % m, swap(m, a);
	}
	return res;
};

auto sol = [](int n, int m, int a, int b) {
	if (a == 0) return min(n, b);
	u64 v1 = floor_sum(n, m, a - 1, b + m - 1);
	u64 v2 = floor_sum(n, m, a, b);
	return int(v1 - v2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m, a, b; cin >> n >> m >> a >> b;
		cout << sol(n, m, a, b) << '\n';
	}
}