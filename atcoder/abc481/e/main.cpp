#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto ccw = [](auto a, auto b, auto c) {
	int x1 = b[0] - a[0], y1 = b[1] - a[1];
	int x2 = c[0] - b[0], y2 = c[1] - b[1];
	return i64(x1) * y2 - i64(x2) * y1;
};

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end(), [](auto a, auto b) {
		bool f1 = a > array{ 0, 0 };
		bool f2 = b > array{ 0, 0 };
		if (f1 != f2) return f1;
		return ccw(a, array{ 0, 0 }, b) > 0;
	});
	int ret = 0;
	for (int i = 0, j = 0; i < n; i++) {
		while (j < i + n && ccw(v[i], array{ 0, 0 }, v[j % n]) >= 0) j++;
		ret = max(ret, j - i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
		cout << sol(n, v) << '\n';
	}
}