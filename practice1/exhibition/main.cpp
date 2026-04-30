#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	for (int i = 0; i < n; i++) {
		auto [x, y] = v[i];
		v[i][0] = x + y;
		v[i][1] = x - y;
	}
	int ret = 1 << 30;
	for (int iter = 0; iter < 2; iter++) {
		int mn_x = 1 << 30, mx_x = -(1 << 30);
		int mn_y = 1 << 30, mx_y = -(1 << 30);
		for (auto& [x, y] : v) {
			x = -x;
			mn_x = min(mn_x, x);
			mx_x = max(mx_x, x);
			mn_y = min(mn_y, y);
			mx_y = max(mx_y, y);
		}
		int lo = -1, hi = 1 << 20;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			bool flag = true;
			for (auto [x, y] : v) {
				if (mn_x <= x && x <= mn_x + mid &&
					mn_y <= y && y <= mn_y + mid) continue;
				if (mx_x - mid <= x && x <= mx_x &&
					mx_y - mid <= y && y <= mx_y) continue;
				flag = false;
				break;
			}
			if (!flag) lo = mid;
			else hi = mid;
		}
		ret = min(ret, hi);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	cout << sol(n, v) << '\n';
}