#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector cand(0, 0);
	for (int i = 1; i <= n; i++) {
		cand.push_back(v[i]);
		sort(cand.begin(), cand.end());
		if (cand.size() > 6) cand.pop_back();
	}
	vector ret(q, 0);
	for (int i = 0; i < q; i++) {
		auto c = cand;
		for (int p : qs[i]) {
			auto it = find(c.begin(), c.end(), v[p]);
			if (it != c.end()) c.erase(it);
		}
		ret[i] = c[0];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	vector qs(q, vector(0, 0));
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < q; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			qs[i].push_back(x);
		}
	}
	auto res = sol(n, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}