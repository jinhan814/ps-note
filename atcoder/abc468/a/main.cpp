#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int res = 0;
	for (int i = 2; i < n; i++) {
		if (v[i - 2] >= v[i - 1]) continue;
		if (v[i - 1] <= v[i]) continue;
		res++;
	}
	cout << res << '\n';
}