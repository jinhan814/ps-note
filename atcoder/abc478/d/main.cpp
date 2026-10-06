#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto qs) {
	vector buc(q + 1, vector(0, pair(0, 0)));
	for (auto [a, b, c] : qs) {
		buc[c].push_back(pair(a, 1));
		buc[c].push_back(pair(b + 1, -1));
	}
	vector ret(n + 2, 0);
	for (int x = 1; x <= q; x++) {
		sort(buc[x].begin(), buc[x].end());
		int cnt = 0;
		for (auto [p, x] : buc[x]) {
			if (cnt == 0) ret[p]++;
			cnt += x;
			if (cnt == 0) ret[p]--;
		}
	}
	for (int i = 1; i <= n; i++) ret[i] += ret[i - 1];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector qs(q, array{ 0, 0, 0 });
	for (auto& [a, b, c] : qs) cin >> a >> b >> c;
	auto res = sol(n, q, qs);
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
}