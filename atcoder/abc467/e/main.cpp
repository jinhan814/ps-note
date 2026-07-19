#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto a, auto b) {
	vector buc(0, array{ 0, 0, 0 });
	auto push = [&](int l, int r, int a, int b) {
		if (l > r) return;
		buc.push_back(array{ l, a, b });
		if (r + 1 < m) buc.push_back(array{ r + 1, -a, -b });
	};
	for (int i = 0, x = 0; i < n; i++) {
		if (i > 0) {
			x = b[i - 1] - x;
			if (x < 0) x += m;
		}
		if (i % 2 == 0) {
			int p = a[i] - x;
			if (p < 0) p += m;
			push(0, p - 1, 1, -p + m);
			push(p, m - 1, 1, -p);
		}
		else {
			int p = x - a[i];
			if (p < 0) p += m;
			push(0, p, -1, p);
			push(p + 1, m - 1, -1, p + m);
		}
	}
	sort(buc.begin(), buc.end());
	i64 ret = i64(1) << 60;
	i64 v1 = 0, v2 = 0;
	for (int i = 0, j = 0; i < buc.size(); i = j) {
		while (j < buc.size() && buc[i][0] == buc[j][0]) {
			v1 += buc[j][1];
			v2 += buc[j][2];
			j++;
		}
		ret = min(ret, v1 * buc[i][0] + v2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n - 1, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n - 1; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}