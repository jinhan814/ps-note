#include <bits/stdc++.h>
using namespace std;

using f64 = double;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector cnt(m + 1, 0);
	vector acc(m + 1, 0);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		cnt[a]++;
		acc[a] += b;
	}
	cout << fixed << setprecision(20);
	for (int i = 1; i <= m; i++) {
		cout << f64(acc[i]) / cnt[i] << '\n';
	}
}