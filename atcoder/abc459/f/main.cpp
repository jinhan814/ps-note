#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector s(0, pair(i64(0), 0));
	for (int i = 0; i < n; i++) {
		i64 acc = v[i] + n - i;
		int len = 1;
		while (s.size()) {
			i64 v1 = (s.back().first + s.back().second - 1) / s.back().second;
			i64 v2 = acc / len;
			if (v1 <= v2) break;
			acc += s.back().first;
			len += s.back().second;
			s.pop_back();
		}
		s.push_back(pair(acc, len));
	}
	vector c(0, i64(0));
	for (auto [acc, len] : s) {
		i64 val = acc / len;
		int rem = acc % len;
		for (int i = 0; i < len - rem; i++) c.push_back(val);
		for (int i = 0; i < rem; i++) c.push_back(val + 1);
	}
	i64 ret = 0, v1 = 0, v2 = 0;
	for (int i = 0; i < n; i++) {
		v1 += v[i] + n - i;
		v2 += c[i];
		ret += v1 - v2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, v) << '\n';
	}
}