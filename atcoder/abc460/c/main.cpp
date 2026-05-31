#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int ret = 0;
	for (int i = 0, j = 0; i < n && j < m; j++) {
		while (i < n && 2 * a[i] < b[j]) i++;
		if (i < n) ret++, i++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	cout << sol(n, m, a, b) << '\n';
}