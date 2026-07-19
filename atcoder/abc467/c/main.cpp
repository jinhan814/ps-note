#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	int ret = 1 << 30;
	for (int x : { 0, 1 }) {
		int acc = 0;
		for (int i = 0; i < n; i++) {
			if (i > 0 && b[i - 1]) x ^= 1;
			if (a[i] != x) acc++;
		}
		ret = min(ret, acc);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n - 1, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n - 1; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}