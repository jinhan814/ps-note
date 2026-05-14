#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto adj, auto qs) {
	vector buc(n + 1, multiset<i64>{});
	auto rec = [&](const auto& self, int cur, int prv, int dep) -> void {
		i64 mx = dep;
		for (auto [nxt, cost] : adj[cur]) {
			if (nxt == prv) continue;
			self(self, nxt, cur, dep + 1);
			mx = max(mx, *buc[nxt].begin());
			buc[cur].insert(*prev(buc[nxt].end()) + cost - 1);
			buc[nxt].erase(prev(buc[nxt].end()));
			if (buc[cur].size() < buc[nxt].size()) swap(buc[cur], buc[nxt]);
			for (i64 x : buc[nxt]) buc[cur].insert(x);
			buc[nxt].clear();
		}
		buc[cur].insert(mx);
		while (buc[cur].size() >= 2 && *next(buc[cur].begin()) <= mx) {
			buc[cur].erase(buc[cur].begin());
		}
	};
	rec(rec, 1, 0, 0);
	vector a(0, i64(0));
	for (i64 x : buc[1]) a.push_back(x);
	vector b(a.size(), i64(0));
	for (int i = a.size() - 2; i >= 0; i--) {
		i64 v1 = a[i + 1] - a[i];
		i64 v2 = a.size() - i - 1;
		b[i] = b[i + 1] + v1 * v2;
	}
	auto query = [&](i64 lim) {
		int lo = 0, hi = a.size();
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (b[mid] >= lim) lo = mid;
			else hi = mid;
		}
		if (b[lo] <= lim) return a[lo];
		i64 v1 = b[lo];
		i64 v2 = a.size() - lo - 1;
		return a[lo] + (v1 - lim + v2 - 1) / v2;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) ret[i] = query(qs[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, pair(0, 0)));
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back(pair(b, c));
		adj[b].push_back(pair(a, c));
	}
	int q; cin >> q;
	vector qs(q, i64(0));
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, adj, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}