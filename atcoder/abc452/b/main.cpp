#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << string(m, '#') << '\n';
	for (int i = 0; i < n - 2; i++) {
		cout << '#' << string(m - 2, '.') << '#' << '\n';
	}
	cout << string(m, '#') << '\n';
}