#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int acc = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		acc ^= v[i];
		if (v[i] % 2 == 1) cnt++;
	}
	if (acc == 0 && cnt == 0) return false;
	if (acc == 1) return false;
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, v) ? "Alice" : "Bob") << '\n';
}