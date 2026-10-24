#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector buc(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		if (v[i] >= k) continue;
		buc.push_back(pair(v[i], 1));
		buc.push_back(pair(min(v[i] + m, k), -1));
	}
	buc.push_back(pair(k, 1));
	sort(buc.begin(), buc.end());
	int ret = 0;
	int pos = 0, cnt = 0;
	for (auto [x, val] : buc) {
		if (cnt == 0) ret += (x - pos + m - 1) / m;
		cnt += val;
		if (cnt == 0) pos = x;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}