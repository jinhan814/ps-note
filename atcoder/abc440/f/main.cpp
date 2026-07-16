#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto v, auto qs) {
	i64 acc_v = 0;
	i64 acc_pq = 0;
	int cnt_v = 0;
	int cnt_pq = 0;
	multiset pq1{ pair(0, 0) }; pq1.clear();
	multiset pq2{ pair(0, 0) }; pq2.clear();
	auto norm = [&] {
		while (pq1.size() < cnt_v) {
			auto [a, b] = *prev(pq2.end());
			acc_pq += a;
			if (b == 2) cnt_pq++;
			pq2.erase(prev(pq2.end()));
			pq1.insert(pair(a, b));
		}
		while (pq1.size() > cnt_v) {
			auto [a, b] = *pq1.begin();
			acc_pq -= a;
			if (b == 2) cnt_pq--;
			pq1.erase(pq1.begin());
			pq2.insert(pair(a, b));
		}
		while (pq1.size() && pq2.size() && pq1.begin()->first < prev(pq2.end())->first) {
			auto [a1, b1] = *pq1.begin();
			auto [a2, b2] = *prev(pq2.end());
			acc_pq -= a1;
			if (b1 == 2) cnt_pq--;
			acc_pq += a2;
			if (b2 == 2) cnt_pq++;
			pq1.erase(pq1.begin());
			pq2.erase(prev(pq2.end()));
			pq1.insert(pair(a2, b2));
			pq2.insert(pair(a1, b1));
		}
	};
	auto push = [&](int i) {
		acc_v += v[i][0];
		if (v[i][1] == 2) cnt_v++;
		pq2.insert(pair(v[i][0], v[i][1]));
		norm();
	};
	auto pop = [&](int i) {
		acc_v -= v[i][0];
		if (v[i][1] == 2) cnt_v--;
		if (auto it = pq1.find(pair(v[i][0], v[i][1])); it != pq1.end()) {
			acc_pq -= v[i][0];
			if (v[i][1] == 2) cnt_pq--;
			pq1.erase(it);
		}
		else {
			pq2.erase(pq2.find(pair(v[i][0], v[i][1])));
		}
		norm();
	};
	auto calc = [&] {
		if (cnt_v == 0) return acc_v;
		if (cnt_pq != cnt_v) return acc_v + acc_pq;
		i64 ret = acc_v + acc_pq - pq1.begin()->first;
		if (cnt_v != n) ret += prev(pq2.end())->first;
		return ret;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < n; i++) {
		push(i);
	}
	for (int i = 0; i < q; i++) {
		auto [p, a, b] = qs[i];
		pop(p);
		v[p][0] = a;
		v[p][1] = b;
		push(p);
		ret[i] = calc();
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n, array{ 0, 0 });
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	for (auto& [a, b, c] : qs) cin >> a >> b >> c, a--;
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}