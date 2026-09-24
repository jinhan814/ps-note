#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, i64 x, i64 y, auto a, auto b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int pos = 0;
	i64 acc = 0;
	while (pos < n && acc + a[pos] <= x + k * y) acc += a[pos++];
	int ret = pos;
	for (int i = 0; i < m; i++) {
		int cnt = (b[i] + k - 1) / k;
		if (y < cnt) break;
		x += k * cnt - b[i];
		y -= cnt;
		while (acc > x + k * y) acc -= a[--pos];
		ret = max(ret, pos + i + 1);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	i64 x, y; cin >> x >> y;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, k, x, y, a, b) << '\n';
}