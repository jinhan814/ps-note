#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string v) {
	int ret = 3, acc = 0;
	for (int i = 0; i < 2 * n; i += 2) {
		if (v[i] == 'O') acc++;
		if (v[i + 1] == 'O') acc--;
		if (acc < 0) ret = min(ret, 1);
		if (acc > 0) ret = min(ret, 2);
		if (i == 2 * n - 2) continue;
		if (!(v[i] == 'O' && v[i + 1] == 'O')) continue;
		if (!(v[i + 2] == 'X' && v[i + 3] == 'X')) continue;
		ret = min(ret, 2);
	}
	if (acc > 0) ret = min(ret, 0);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string v(2 * n, 0);
	for (int i = 0; i < 2 * n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}