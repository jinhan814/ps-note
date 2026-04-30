#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto ccw = [](auto a, auto b, auto c) {
	i64 x1 = b[0] - a[0], y1 = b[1] - a[1];
	i64 x2 = c[0] - b[0], y2 = c[1] - b[1];
	return x1 * y2 - x2 * y1;
};

auto sol = [](int n, auto v) {
	for (int i = 1; i < n; i++) {
		if (v[0][1] < v[i][1]) continue;
		swap(v[0], v[i]);
	}
	sort(v.begin() + 1, v.end(), [&](auto a, auto b) {
		bool f1 = v[0] < a;
		bool f2 = v[0] < b;
		if (f1 != f2) return f1;
		i64 res = ccw(v[0], a, b);
		if (res != 0) return res > 0;
		int d1 = abs(v[0][0] - a[0]) + abs(v[0][1] - a[1]);
		int d2 = abs(v[0][0] - b[0]) + abs(v[0][1] - b[1]);
		return d1 < d2;
	});
	vector cand(0, 0);
	vector buc(n, vector(0, 0));
	vector pref(n, vector(0, 0));
	vector suff(n, vector(0, 0));
	for (int l = 1, r = 1; l < n; l = r) {
		while (r < n && ccw(v[0], v[l], v[r]) == 0) r++;
		for (int cur = l; cur < r; cur++) {
			if (cur != l && cur != r - 1) continue;
			sort(cand.begin(), cand.end(), [&](int i, int j) {
				return ccw(v[cur], v[i], v[j]) > 0;
			});
			buc[cur] = cand;
			pref[cur].resize(cand.size());
			suff[cur].resize(cand.size());
			for (int i = 0; i < cand.size(); i++) {
				int prv = buc[cur][i];
				int val = 0;
				int lo = -1, hi = buc[prv].size();
				while (lo + 1 < hi) {
					int mid = (lo + hi) / 2;
					if (ccw(v[buc[prv][mid]], v[prv], v[cur]) > 0) lo = mid;
					else hi = mid;
				}
				if (lo >= 0) val = pref[prv][lo] + 1;
				suff[cur][i] = val;
				val = 0;
				hi = buc[prv].size();
				while (lo + 1 < hi) {
					int mid = (lo + hi) / 2;
					if (ccw(v[buc[prv][mid]], v[prv], v[cur]) >= 0) lo = mid;
					else hi = mid;
				}
				if (hi < buc[prv].size()) val = suff[prv][hi] + 1;
				pref[cur][i] = val;
			}
			for (int i = 1; i < cand.size(); i++) {
				pref[cur][i] = max(pref[cur][i], pref[cur][i - 1]);
			}
			for (int i = cand.size() - 2; i >= 0; i--) {
				suff[cur][i] = max(suff[cur][i], suff[cur][i + 1]);
			}
		}
		cand.push_back(l);
		if (r - 1 != l) cand.push_back(r - 1);
	}
	int mx = -1, a = -1, b = -1;
	for (int cur = 1; cur < n; cur++) {
		if (buc[cur].empty()) continue;
		if (mx >= pref[cur].back()) continue;
		int i = buc[cur].size() - 1;
		while (i - 1 >= 0 && pref[cur][i - 1] == pref[cur].back()) i--;
		mx = pref[cur][i];
		a = cur;
		b = buc[cur][i];
	}
	if (mx < 1) return vector(0, array{ 0, 0 });
	vector ret{ v[a], v[b] };
	for (int f = 1; mx > 0; mx--, f ^= 1) {
		if (f == 0) {
			int i = 0;
			while (i + 1 < buc[b].size()) {
				if (ccw(v[buc[b][i + 1]], v[b], v[a]) <= 0) break;
				i++;
			}
			while (i - 1 >= 0) {
				if (pref[b][i - 1] != pref[b][i]) break;
				i--;
			}
			a = b;
			b = buc[b][i];
			ret.push_back(v[b]);
		}
		else {
			int i = buc[b].size() - 1;
			while (i - 1 >= 0) {
				if (ccw(v[buc[b][i - 1]], v[b], v[a]) >= 0) break;
				i--;
			}
			while (i + 1 < buc[b].size()) {
				if (suff[b][i + 1] != suff[b][i]) break;
				i++;
			}
			a = b;
			b = buc[b][i];
			ret.push_back(v[b]);
		}
	}
	if (ret.size() % 2 == 0) ret.pop_back();
	ret.push_back(v[0]);
	reverse(ret.begin(), ret.end());
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
	auto res = sol(n, v);
	cout << res.size() << '\n';
	for (auto [a, b] : res) cout << a << ' ' << b << '\n';
}