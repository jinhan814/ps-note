#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(n, 0);
	ret[0] = (v[n - 1] - v[0]) / 2;
	ret[n - 1] = (v[n - 1] - v[0]) / 2;
	for (int i = 1; i <= n - 2; i++) {
		int v1 = max(v[n - 1] - v[i], v[i + 1] - v[0]) / 2;
		int v2 = max(v[i] - v[0], v[n - 1] - v[i - 1]) / 2;
		ret[i] = min(v1, v2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}