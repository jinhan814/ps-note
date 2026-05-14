#include <bits/stdc++.h>
using namespace std;

using f64 = double;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector cnt(3, vector(7, 0));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			int x; cin >> x;
			cnt[i][x]++;
		}
	}
	f64 res = 0;
	vector p{ 0, 1, 2 };
	do {
		f64 val = 1;
		for (int i = 0; i < 3; i++) val *= f64(cnt[p[i]][i + 4]) / 6;
		res += val;
	}
	while (next_permutation(p.begin(), p.end()));
	cout << fixed << setprecision(20);
	cout << res << '\n';
}