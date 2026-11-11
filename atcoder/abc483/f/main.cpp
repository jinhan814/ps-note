#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	vector acc(401, vector(400, 0));
	vector p(500'001, i64(0));
	int cnt = 0;
	for (auto [a, b] : v) {
		if (b > 400) continue;
		for (int x = 0; x < b; x++) acc[b][x] += (x + a) % b;
	}
	for (auto [a, b] : v) {
		if (b <= 400) continue;
		cnt++;
		p[0] += a;
		for (int i = b - a; i <= 500'000; i += b) p[i] -= b;
	}
	for (int i = 1; i <= 500'000; i++) {
		p[i] += p[i - 1] + cnt;
	}
	auto calc = [&](int x) {
		i64 ret = p[x];
		for (int i = 1; i <= 400; i++) ret += acc[i][x % i];
		return ret;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) ret[i] = calc(qs[i]);
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