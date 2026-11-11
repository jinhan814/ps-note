#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector p(500'001, i64(0));
	sort(v.begin(), v.end());
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		auto [a, b] = v[i];
		p[0] += i64(j - i) * a;
		for (int x = b - a; x <= 500'000; x += b) p[x] -= i64(j - i) * b;
	}
	for (int i = 1; i <= 500'000; i++) p[i] += p[i - 1] + n;
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) ret[i] = p[qs[i]];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	int q; cin >> q;
	vector qs(q, 0);
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}