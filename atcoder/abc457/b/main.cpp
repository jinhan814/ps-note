#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(0, 0));
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		v[i].resize(m);
		for (int& x : v[i]) cin >> x;
	}
	int a, b; cin >> a >> b;
	cout << v[a - 1][b - 1] << '\n';
}