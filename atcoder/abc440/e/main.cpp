#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int k, auto v) {
	sort(v.begin(), v.end(), greater{});
	set s{ vector(0, 0) }; s.clear();
	set pq{ pair(i64(0), vector(0, 0)) }; pq.clear();
	auto push = [&](auto c) {
		if (s.count(c)) return;
		i64 acc = 0;
		for (int i = 0; i < n; i++) acc += i64(c[i]) * v[i];
		s.insert(c);
		pq.insert(pair(acc, c));
	};
	vector c(n, 0);
	c[0] = m;
	push(c);
	vector ret(0, i64(0));
	while (ret.size() < k) {
		auto [val, c] = *prev(pq.end());
		pq.erase(prev(pq.end()));
		ret.push_back(val);
		for (int i = 1; i < n; i++) {
			if (c[i - 1] == 0) continue;
			c[i - 1]--;
			c[i]++;
			push(c);
			c[i - 1]++;
			c[i]--;
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