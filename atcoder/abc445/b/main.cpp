#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int mx = 0;
	for (int i = 0; i < n; i++) {
		if (mx >= v[i].size()) continue;
		mx = v[i].size();
	}
	vector ret(n, string{});
	for (int i = 0; i < n; i++) {
		int x = (mx - v[i].size()) / 2;
		ret[i] += string(x, '.');
		ret[i] += v[i];
		ret[i] += string(x, '.');
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}