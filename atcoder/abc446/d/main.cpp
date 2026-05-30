#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	map c{ pair(0, 0) }; c.clear();
	for (int x : v) c[x] = c[x - 1] + 1;
	int ret = 0;
	for (auto [a, b] : c) ret = max(ret, b);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}