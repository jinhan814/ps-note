#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 acc = 0;
	vector buc(0, 0);
	v.insert(v.begin(), 1);
	v.push_back(1);
	for (int i = 1; i < v.size(); i++) {
		if (v[i - 1] == v[i]) continue;
		int x = v[i] - v[i - 1];
		if (x < 0) x += n;
		acc += x;
		buc.push_back(n - 2 * x);
	}
	sort(buc.begin(), buc.end());
	i64 ret = acc;
	for (int i = 0; i < acc / n; i++) ret += buc[i];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, 0);
	for (int i = 0; i < m; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}