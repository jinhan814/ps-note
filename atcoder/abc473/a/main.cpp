#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int res = 0;
	for (int i = n / 2; i < n; i++) res += v[i];
	cout << res << '\n';
}