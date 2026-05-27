#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(n, 0);
	iota(ret.begin(), ret.end(), 1);
	sort(ret.begin() + 1, ret.end(), [&](int i, int j) {
		if (v[i][0] / 80'000 != v[j][0] / 80'000) return v[i][0] < v[j][0];
		if (v[i][0] / 80'000 % 2 == 0) return v[i][1] < v[j][1];
		return v[i][1] > v[j][1];
	});
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0] >> v[i][1];
	auto res = sol(n, v);
	for (int i : res) cout << i << ' ';
	cout << '\n';
}