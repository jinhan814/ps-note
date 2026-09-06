#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	for (int i = 0; i + 9 < n; i += 10) {
		int mask = 0;
		for (int j = 0; j < 10; j++) {
			if (v[i + j] <= i) return false;
			if (v[i + j] > i + 10) return false;
			if (mask >> (v[i + j] - i) & 1) return false;
			mask |= 1 << (v[i + j] - i);
		}
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, v) ? "Yes" : "No") << '\n';
}