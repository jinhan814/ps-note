#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	bitset<10'001> b;
	b[0] = 1;
	for (int x : v) b |= b << x;
	return b.count();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}