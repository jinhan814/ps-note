#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	int ret = 0;
	while (next_permutation(a.begin(), a.end()) && a < b) ret++;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	cout << sol(n, a, b) << '\n';
}