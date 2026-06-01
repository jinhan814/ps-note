#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	int res = 0;
	for (int i = 1; i <= n; i++) {
		int x = i, s = 0;
		while (x > 0) s += x % 10, x /= 10;
		if (s == k) res++;
	}
	cout << res << '\n';
}