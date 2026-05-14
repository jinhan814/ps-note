#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	if (a == b) return true;
	for (int i = 0; i + 2 < n; i++) {
		if (b[i] < b[i + 1] && b[i + 1] < b[i + 2]) return true;
		if (b[i] > b[i + 1] && b[i + 1] > b[i + 2]) return true;
	}
	return false;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << (sol(n, a, b) ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
}