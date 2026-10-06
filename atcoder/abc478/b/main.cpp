#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			for (int k = j + 1; k <= n; k++) {
				if (i + j + k > m) break;
				ret = max(ret, v[i] + v[j] + v[k]);
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}