#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	vector ret(n, vector(n, 0));
	int val = 0;
	for (int j = n - 2; j >= 0; j--) {
		int acc = 0;
		for (int i = 1; i <= n - 1; i++) {
			int mn = 0, mx = 0;
			for (int k = i; k <= n - 1; k++) {
				mn += ret[k][n - 1];
				mx += ret[k][j + 1];
			}
			for (int k = j + 2; k <= n - 1; k++) {
				mn += ret[i][k - 1];
				mx += ret[n - 1][k];
			}
			ret[i][j] = (val + 1) - (acc + mn);
			acc += ret[i][j];
			val = acc + mx;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	auto res = sol(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
}