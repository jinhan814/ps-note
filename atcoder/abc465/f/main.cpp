#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int q, auto a, auto b, auto qs) {
	vector p(1'771'561, i64(0));
	auto f = [&](string s) {
		int x = 0;
		for (int i = 0; i < 6; i++) x = 11 * x + (s[i] - 48 + 1);
		return x;
	};
	for (int i = 0; i < n; i++) {
		p[f(a[i])] += b[i];
	}
	for (int iter = 0; iter < 6; iter++) {
		for (int x = 0; x <= 999'999; x++) {
			string s = to_string(x);
			s = string(6 - s.size(), '0') + s;
			string t = s;
			t[iter]--;
			p[f(s)] += p[f(t)];
		}
	}
	auto calc = [&](string l, string r) {
		for (int i = 0; i < 6; i++) {
			if (l[i] <= r[i]) continue;
			return i64(0);
		}
		i64 ret = 0;
		for (int mask = 0; mask < 1 << 6; mask++) {
			string s(6, 0);
			for (int i = 0; i < 6; i++) {
				if (mask >> i & 1) s[i] = l[i] - 1;
				else s[i] = r[i];
			}
			if (__builtin_popcount(mask) % 2 == 0) ret += p[f(s)];
			else ret -= p[f(s)];
		}
		return ret;
	};
	vector ret(q, i64(0));
	for (int i = 0; i < q; i++) {
		auto [l, r] = qs[i];
		ret[i] = calc(l, r);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, string{});
	vector b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	int q; cin >> q;
	vector qs(q, array{ string{}, string{} });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(n, q, a, b, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}