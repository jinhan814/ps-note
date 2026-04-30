#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector c(n, 0);
	int ret = 0, acc = 0;
	while (acc < 2 * n) {
		bool flag = false;
		for (int i = 0; i < n; i++) {
			if (c[i] == 2 || acc < v[i][1]) continue;
			ret++;
			acc += 2 - c[i];
			c[i] = 2;
			flag = true;
		}
		if (flag) continue;
		int p = -1;
		for (int i = 0; i < n; i++) {
			if (c[i] != 0 || acc < v[i][0]) continue;
			if (p == -1 || v[p][1] < v[i][1]) p = i;
		}
		if (p == -1) return -1;
		ret++;
		acc++;
		c[p] = 1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int iter = 1; iter <= tc; iter++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
		int res = sol(n, v);
		cout << "Case #" << iter << ": ";
		if (res == -1) cout << "Too Bad" << '\n';
		else cout << res << '\n';
	}
}