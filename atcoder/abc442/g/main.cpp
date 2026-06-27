#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	vector buc(4, vector(0, pair(0, 0)));
	for (auto [a, b, c] : v) {
		buc[a].push_back(pair(b, c));
	}
	for (int i = 1; i <= 3; i++) {
		buc[i].push_back(pair(0, 1 << 30));
		sort(buc[i].begin(), buc[i].end());
		vector cand(0, pair(0, 0));
		while (cand.size() < 6 / i) {
			auto [v1, v2] = buc[i].back();
			buc[i].pop_back();
			while (cand.size() < 6 / i && v2 > 0) {
				cand.push_back(pair(v1, 1));
				v2--;
			}
			if (v2 > 0) {
				buc[i].push_back(pair(v1, v2));
			}
		}
		for (auto [v1, v2] : cand) {
			buc[i].push_back(pair(v1, v2));
		}
		sort(buc[i].begin(), buc[i].end(), [](auto a, auto b) {
			if (a.first != b.first) return a.first > b.first;
			return a.second < b.second;
		});
	}
	i64 ret = 0;
	for (int c1 = 0; c1 < 6; c1++) {
		for (int c2 = 0; c2 < 3; c2++) {
			for (int c3 = 0; c3 < 2; c3++) {
				int rem = m - c1 - 2 * c2 - 3 * c3;
				if (rem < 0) continue;
				i64 acc = 0;
				vector cand(0, pair(i64(0), 0));
				for (int i = 1; i <= 3; i++) {
					int lim = i == 1 ? c1 : i == 2 ? c2 : c3;
					i64 val = 0;
					int cnt = 0;
					for (int j = 0; j < lim; j++) {
						acc += buc[i][j].first;
					}
					for (int j = lim; j < buc[i].size(); j++) {
						auto [v1, v2] = buc[i][j];
						if (cnt + v2 >= 6 / i) {
							cand.push_back(pair(val + i64(v1) * (6 / i - cnt), 1));
							v2 -= 6 / i - cnt;
							val = 0;
							cnt = 0;
						}
						if (v2 >= 6 / i) {
							cand.push_back(pair(i64(v1) * (6 / i), v2 / (6 / i)));
							v2 %= 6 / i;
						}
						val += i64(v1) * v2;
						cnt += v2;
					}
				}
				sort(cand.begin(), cand.end(), greater{});
				for (auto [v1, v2] : cand) {
					int cnt = min(rem / 6, v2);
					acc += v1 * cnt;
					rem -= 6 * cnt;
				}
				ret = max(ret, acc);
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0, 0 });
	for (auto& [a, b, c] : v) cin >> a >> b >> c;
	cout << sol(n, m, v) << '\n';
}