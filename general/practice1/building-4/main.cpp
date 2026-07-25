#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector mn(2 * n, array{ 1 << 30, 1 << 30 });
	vector mx(2 * n, array{ -(1 << 30), -(1 << 30) });
	mn[0][0] = mx[0][0] = 0;
	mn[0][1] = mx[0][1] = 1;
	for (int i = 1; i < 2 * n; i++) {
		for (int a = 0; a < 2; a++) {
			for (int b = 0; b < 2; b++) {
				if (v[i - 1][a] > v[i][b]) continue;
				mn[i][b] = min(mn[i][b], mn[i - 1][a] + (b == 1));
				mx[i][b] = max(mx[i][b], mx[i - 1][a] + (b == 1));
			}
		}
	}
	int i = 2 * n - 1, j = 0, x = n;
	if (!(mn[i][j] <= x && x <= mx[i][j])) j++;
	if (!(mn[i][j] <= x && x <= mx[i][j])) return string("-1");
	string ret(2 * n, 0);
	while (i > 0) {
		ret[i] = "AB"[j];
		int val = v[i][j];
		i--;
		if (j == 1) j = 0, x--;
		if (v[i][0] > val || mn[i][0] > x || mx[i][0] < x) j++;
	}
	ret[0] = "AB"[j];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(2 * n, array{ 0, 0 });
	for (int i = 0; i < 2 * n; i++) cin >> v[i][0];
	for (int i = 0; i < 2 * n; i++) cin >> v[i][1];
	cout << sol(n, v) << '\n';
}