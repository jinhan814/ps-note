#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto ccw = [](auto a, auto b, auto c) {
	i64 x1 = b[0] - a[0];
	i64 y1 = b[1] - a[1];
	i64 x2 = c[0] - b[0];
	i64 y2 = c[1] - b[1];
	return abs(1LL * x1 * y2 - 1LL * x2 * y1);
};

int main() {
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	vector c(n + 1, 0);
	auto get = [&] {
		vector buc(0, 0);
		for (int i = 1; i <= n; i++) {
			if (c[i]) continue;
			buc.push_back(i);
		}
		int p = -1;
		i64 opt = 1LL << 60;
		for (int i = 0; i < buc.size(); i++) {
			auto a = v[buc[i ? i - 1 : buc.size() - 1]];
			auto b = v[buc[i]];
			auto c = v[buc[i + 1 < buc.size() ? i + 1 : 0]];
			i64 area = ccw(a, b, c);
			if (opt > area) p = buc[i], opt = area;
		}
		return p;
	};
	if (n & 1) {
		cout << "Beatrice" << endl;
		for (int iter = 0; iter < n / 2; iter++) {
			int x; cin >> x;
			c[x] = 1;
			int y = get();
			cout << y << endl;
			c[y] = 1;
		}
	}
	else {
		cout << "Alberto" << endl;
		for (int iter = 0; iter < n / 2 - 1; iter++) {
			int y = get();
			cout << y << endl;
			c[y] = 1;
			int x; cin >> x;
			c[x] = 1;
		}
	}
}