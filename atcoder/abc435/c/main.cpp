#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int ret = 0;
	int mx = 1;
	for (int i = 0; i < n && i < mx; i++) {
		ret++;
		mx = max(mx, i + v[i]);
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