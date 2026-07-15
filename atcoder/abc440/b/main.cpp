#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	vector c(n, 0);
	iota(c.begin(), c.end(), 1);
	sort(c.begin(), c.end(), [&](int i, int j) {
		return v[i] < v[j];
	});
	cout << c[0] << ' ' << c[1] << ' ' << c[2] << '\n';
}