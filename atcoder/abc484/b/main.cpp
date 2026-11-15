#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	if (v.back() != 9) return -1;
	return v[0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}