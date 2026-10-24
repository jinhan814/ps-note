#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector ret(n, 0);
	for (string s : b) {
		vector cand(0, 0);
		for (int i = 0; i < n; i++) {
			if (a[i].size() != s.size()) continue;
			int cnt = 0;
			for (int j = 0; j < s.size(); j++) if (a[i][j] != s[j]) cnt++;
			if (cnt == 0) cand.clear();
			if (cnt <= 1) cand.push_back(i);
			if (cnt == 0) break;
		}
		if (cand.size() != 1) continue;
		ret[cand[0]]++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, string{});
	vector b(m, string{});
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	auto res = sol(n, m, a, b);
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}