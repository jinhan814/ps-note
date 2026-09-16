#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, i64 k, auto v) {
	for (int i = 1; i < n; i++) v[i] += v[i - 1];
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			if (i > m || j < m) continue;
			i64 v1 = v[j - 1] - v[i - 1];
			i64 v2 = min(v[m - 1] - v[i - 1], v[j - 1] - v[m - 1]);
			if (v1 + v2 <= k) ret = max(ret, j - i + 1);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	i64 k; cin >> k;
	vector v(n, i64(0));
	for (int i = 1; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}