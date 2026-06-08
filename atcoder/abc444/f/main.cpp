#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 m, auto v) {
	auto check = [&](int lim) {
		i64 acc = 0;
		int cnt = 0;
		vector buc(0, pair(0, i64(0)));
		for (int i = 0; i < n; i++) {
			acc += v[i];
			if (v[i] >= lim) cnt++;
			int v1 = v[i], v2 = v[i] + 1;
			i64 c1 = 1, c2 = 0;
			while (v1 >= 2 * lim - 1) {
				int nv1 = v1 / 2, nv2 = (v2 + 1) / 2;
				i64 nc1 = c1, nc2 = c2;
				if ((v1 + 1) / 2 == nv1) nc1 += c1;
				else nc2 += c1;
				if (v2 / 2 == nv1) nc1 += c2;
				else nc2 += c2;
				tie(v1, v2, c1, c2) = tuple(nv1, nv2, nc1, nc2);
			}
			if (v2 == 2 * lim - 1) v2 = lim;
			if (v1 >= lim) buc.push_back(pair(v1, c1));
			if (v2 >= lim) buc.push_back(pair(v2, c2));
		}
		sort(buc.begin(), buc.end());
		i64 rem = (n + m + 1) / 2;
		if (rem > cnt + m) return false;
		for (auto [a, b] : buc) {
			i64 x = min(rem, b);
			acc -= a * x;
			rem -= x;
			if (rem == 0) break;
		}
		if (rem > 0) return false;
		return acc >= (n + m - 1) / 2;
	};
	int lo = 1, hi = 1 << 30;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		i64 m; cin >> m;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, m, v) << '\n';
	}
}