#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(n + 1, 0);
	for (int i = n; i >= 1; i--) {
		if (v[i] == i) ret[i] = i;
		else ret[i] = ret[v[i]];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}