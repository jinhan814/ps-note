#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector l(n, vector(n, 1 << 30));
	vector r(n, vector(n, -(1 << 30)));
	l[0][0] = 0;
	r[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i + 1 < n) {
				l[i + 1][j] = min(l[i + 1][j], l[i][j] + (v[i + 1][j] == '@'));
				r[i + 1][j] = max(r[i + 1][j], r[i][j] + (v[i + 1][j] == '@'));
			}
			if (j + 1 < n) {
				l[i][j + 1] = min(l[i][j + 1], l[i][j] + (v[i][j + 1] == '@'));
				r[i][j + 1] = max(r[i][j + 1], r[i][j] + (v[i][j + 1] == '@'));
			}
		}
	}
	vector ret(2 * n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ret[l[i][j]]++;
			ret[r[i][j] + 1]--;
		}
	}
	for (int i = 1; i <= 2 * n - 2; i++) ret[i] += ret[i - 1];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string(0, 0));
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 0; i <= 2 * n - 2; i++) cout << res[i] << '\n';
}