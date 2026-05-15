#include <bits/stdc++.h>
using namespace std;

auto ccw = [](auto a, auto b, auto c) {
	int x1 = b[0] - a[0], y1 = b[1] - a[1];
	int x2 = c[0] - b[0], y2 = c[1] - b[1];
	int res = x1 * y2 - x2 * y1;
	return res ? res > 0 ? 1 : -1 : 0;
};

auto sol = [](int n, auto v, string s) {
	int p = 0;
	for (int i = 1; i < n; i++) {
		if (v[p] <= v[i]) continue;
		p = i;
	}
	vector ret(1, p);
	vector c(n, false); c[p] = true;
	for (int iter = 0; iter < n - 1; iter++) {
		for (int i = 0; i < n; i++) {
			if (c[i]) continue;
			bool flag = true;
			for (int j = 0; j < n; j++) {
				if (c[j]) continue;
				if (i == j) continue;
				if (s[iter] == 'R' && ccw(v[p], v[i], v[j]) < 0) continue;
				if (s[iter] == 'L' && ccw(v[p], v[i], v[j]) > 0) continue;
				flag = false;
				break;
			}
			if (!flag) continue;
			ret.push_back(i);
			c[i] = true;
			p = i;
			break;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	string s; cin >> s;
	auto res = sol(n, v, s);
	for (int i = 0; i < n; i++) cout << res[i] + 1 << ' ';
	cout << '\n';
}