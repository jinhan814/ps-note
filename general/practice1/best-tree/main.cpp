#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	if (n == 2) return 1;
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (v[i] > 1) cnt++;
	return min(n / 2, cnt);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}