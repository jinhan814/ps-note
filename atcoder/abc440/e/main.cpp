#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v) {
	sort(v.begin(), v.end(), greater{});
	vector ret(0, i64(0));
	multiset pq{ tuple(i64(m) * v[0], 0, 0, m) };
	while (ret.size() < k) {
		auto [val, i, a, b] = *prev(pq.end());
		pq.erase(prev(pq.end()));
		ret.push_back(val);
		if (a > 0) {
			pq.insert(tuple(val - v[i - 1] + v[i], i, a - 1, b + 1));
		}
		if (i + 1 < n) {
			pq.insert(tuple(val - v[i] + v[i + 1], i + 1, b - 1, 1));
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, m, k, v);
	for (int i = 0; i < k; i++) cout << res[i] << '\n';
}