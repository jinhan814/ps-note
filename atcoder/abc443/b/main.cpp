#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	int res = 0;
	while (1) {
		k -= n;
		if (k <= 0) break;
		n++;
		res++;
	}
	cout << res << '\n';
}