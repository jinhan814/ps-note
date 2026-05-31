#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	int res = 0;
	while (m > 0) m = n % m, res++;
	cout << res << '\n';
}