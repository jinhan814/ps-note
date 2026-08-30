#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	vector c(k, 0);
	for (int x : v) c[x - 1]++;
	sort(c.begin(), c.end(), greater{});
	int ret = 0;
	for (int i = 0; i < k; i++) {
		int mx = i > 0 ? c[0] : c[1];
		if (c[i] + 1 >= mx) ret++;
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