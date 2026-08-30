#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector c(101, 0);
	for (int x : v) c[x] ^= 1;
	int ret = 0;
	for (int i = 1; i <= 100; i++) {
		if (c[i] == 0) continue;
		ret += i;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}