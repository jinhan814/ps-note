#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		cout << (m > x) << '\n';
		if (m > x) m = x;
	}
}