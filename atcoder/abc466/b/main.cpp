#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m + 1, -1);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		v[a] = max(v[a], b);
	}
	for (int i = 1; i <= m; i++) cout << v[i] << ' ';
	cout << '\n';
}