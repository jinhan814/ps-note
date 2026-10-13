#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto a, auto b) {
	i64 ret = 0;
	for (int mask = 0; mask < 1 << n; mask++) {
		i64 v1 = 0, v2 = 0;
		for (int i = 0; i < n; i++) {
			if (~mask >> i & 1) continue;
			v1 += a[i];
			v2 += b[i];
		}
		if (v2 <= m) ret = max(ret, v1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	cout << sol(n, m, a, b) << '\n';
}