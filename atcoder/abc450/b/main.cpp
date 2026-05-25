#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			for (int k = j + 1; k <= n; k++) {
				if (v[i][j] + v[j][k] >= v[i][k]) continue;
				return true;
			}
		}
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, vector(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) cin >> v[i][j];
	}
	cout << (sol(n, v) ? "Yes" : "No") << '\n';
}