#include <bits/stdc++.h>
using namespace std;

auto calc = [](int n, string s) {
	vector ret(2 * n, 0);
	for (int i = 0, x = n; i < n; i++) {
		int nx = x + (s[i] == '1' ? 1 : -1);
		ret[min(x, nx)]++;
		x = nx;
	}
	return ret;
};

auto sol = [](int n, string a, string b) {
	if (calc(n, a) != calc(n, b)) return vector(1, pair(-1, -1));
	vector ret(0, pair(0, 0));
	while (a != b) {
		int l = 0;
		while (a[l] == b[l]) l++;
		int r = l;
		int x = a[r] == '1' ? 1 : -1;
		while (r < n && (a[r] != a[l] || x != 0)) {
			r++;
			x += a[r] == '1' ? 1 : -1;
		}
		assert(r < n);
		ret.push_back(pair(l, r));
		reverse(a.begin() + l, a.begin() + r + 1);
		for (int i = l; i <= r; i++) a[i] ^= 1;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string a, b; cin >> a >> b;
	auto res = sol(n, a, b);
	if (res != vector(1, pair(-1, -1))) {
		cout << "YES" << '\n';
		cout << res.size() << '\n';
		for (auto [l, r] : res) cout << l + 1 << ' ' << r + 1 << '\n';
	}
	else {
		cout << "NO" << '\n';
	}
}