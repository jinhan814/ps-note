#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	for (int i = 0; i < n; i++) v[i] %= k;
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	if (v.size() == 1) return 0;
	int ret = v.back() - v[0];
	for (int i = 1; i < v.size(); i++) {
		ret = min(ret, k - (v[i] - v[i - 1]));
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