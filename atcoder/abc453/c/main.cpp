#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	int ret = -1;
	for (int mask = 0; mask < 1 << n; mask++) {
		i64 p = 1;
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			i64 np = p;
			if (mask >> i & 1) np += 2 * v[i];
			else np -= 2 * v[i];
			if ((p > 0) ^ (np > 0)) cnt++;
			p = np;
		}
		ret = max(ret, cnt);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}