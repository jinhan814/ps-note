#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	sort(v.begin(), v.end());
	for (int i = k; i < n; i++) v[i] += v[i - k];
	int p = 0;
	while (p < n && v[p] <= m) p++;
	return p;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}