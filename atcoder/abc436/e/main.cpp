#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector c(n + 1, false);
	i64 ret = 0;
	for (int i = 1; i <= n; i++) {
		if (c[i]) continue;
		int x = i, cnt = 0;
		while (!c[x]) c[x] = true, x = v[x], cnt++;
		ret += i64(cnt) * (cnt - 1) / 2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}