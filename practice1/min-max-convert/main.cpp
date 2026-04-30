#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto a, auto b) {
	auto cmp = [](int a, int b, int c, int d) {
		if (a == b && c == d) return true;
		if (a < b && c < d) return true;
		if (a > b && c > d) return true;
		return false;
	};
	vector f(n, 0);
	for (int i = 0; i < n; i++) {
		if (i > 0) f[i] = f[i - 1];
		while (f[i] < n && b[i] != a[f[i]]) f[i]++;
		if (f[i] == n) return vector(1, array{ -1, -1, -1 });
	}
	vector ret(0, array{ 0, 0, 0 });
	for (int l = 0, r = 0; l < n; l = r) {
		while (r < n && cmp(f[l], l, f[r], r)) r++;
		if (f[l] < l) {
			vector cand(0, pair(0, 0));
			for (int i = l, j = l; i < r; i = j) {
				while (j < r && f[i] == f[j]) j++;
				cand.push_back(pair(i, j - 1));
			}
			for (int i = cand.size() - 1; i >= 0; i--) {
				int p = f[cand[i].first];
				for (int l = p + 1, r = p + 1; l <= cand[i].second; l = r) {
					while (r <= cand[i].second && cmp(a[p], a[l], a[p], a[r])) r++;
					if (a[p] == a[l]) continue;
					ret.push_back(array{ p, r - 1, a[p] < a[l] ? 0 : 1 });
					for (int j = l; j < r; j++) a[j] = a[p];
				}
			}
		}
		if (f[l] > l) {
			vector cand(0, pair(0, 0));
			for (int i = l, j = l; i < r; i = j) {
				while (j < r && f[i] == f[j]) j++;
				cand.push_back(pair(i, j - 1));
			}
			for (int i = 0; i < cand.size(); i++) {
				int p = f[cand[i].first];
				for (int l = p - 1, r = p - 1; r >= cand[i].first; r = l) {
					while (l >= cand[i].first && cmp(a[p], a[r], a[p], a[l])) l--;
					if (a[p] == a[r]) continue;
					ret.push_back(array{ l + 1, p, a[p] < a[r] ? 0 : 1 });
					for (int j = r; j > l; j--) a[j] = a[p];
				}
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	auto res = sol(n, a, b);
	if (res == vector(1, array{ -1, -1, -1 })) { 
		cout << -1 << '\n';
	}
	else {
		cout << res.size() << '\n';
		for (auto [l, r, f] : res) {
			cout << "mM"[f] << ' ' << l + 1 << ' ' << r + 1 << '\n';
		}
	}
}