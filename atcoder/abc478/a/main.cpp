#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	int q = m / n, r = m % n;
	for (int i = 0; i < r; i++) cout << q + 1 << ' ';
	for (int i = r; i < n; i++) cout << q << ' ';
	cout << '\n';
}