#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto a, auto b, auto qs) {
	vector p(n + 1, i64(0));
	set pq{ pair(0, 0) };
	pq.clear();
	for (int i = 1; i <= n; i++) {
		p[i] = p[i - 1] + a[i];
		pq.insert(pair(b[i], i));
	}
	while (pq.size()) {
		auto [x, i] = *pq.begin();
		pq.erase(pq.begin());
		int p1 = i > 1 ? i - 1 : n;
		int p2 = i < n ? i + 1 : 1;
		if (b[p1] > x + a[p1]) {
			pq.erase(pair(b[p1], p1));
			pq.insert(pair(b[p1] = x + a[p1], p1));
		}
		if (b[p2] > x + a[i]) {
			pq.erase(pair(b[p2], p2));
			pq.insert(pair(b[p2] = x + a[i], p2));
		}
	}
	auto calc = [&](int p1, int p2) {
		if (p2 == n + 1) return b[p1];
		int ret = b[p1] + b[p2];
		i64 d = p[p2 - 1] - p[p1 - 1];
		if (2 * d > p[n]) d = p[n] - d;
		if (ret > d) ret = d;
		return ret;
	};
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto [p1, p2] = qs[i];
		ret[i] = calc(p1, p2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector a(n + 1, 0), b(n + 1, 0);
	vector qs(q, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, a, b, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}