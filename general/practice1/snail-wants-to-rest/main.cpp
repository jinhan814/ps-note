#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ i64(0), i64(0) });
	for (int i = 1; i <= n; i++) {
		cin >> v[i][0] >> v[i][1];
		v[0][0] = min(v[0][0], v[i][0] - v[i][1]);
	}
	i64 acc = 0;
	for (int i = 1; i <= n; i++) {
		acc += abs(v[i][0] - v[i - 1][0]);
		acc += abs(v[i][1] - v[i - 1][1]);
	}
	cout << acc - (v[n][0] - v[0][0]) << '\n';
}