#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] != k) continue;
		ret++;
	}
	for (int i = 1; i < n; i++) {
		int a = v[i - 1], b = v[i];
		if (a > b) swap(a, b);
		if (k <= a || b <= k) continue;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}