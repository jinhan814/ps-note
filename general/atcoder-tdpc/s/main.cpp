#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'000'007;

auto sol = [](int n, int m) {
	auto conv = [](string s) {
		string c(6, 0);
		char p = '1';
		for (int i = 0; i < s.size(); i++) {
			if (s[i] < '2') continue;
			if (c[s[i] - '0'] == 0) c[s[i] - '0'] = ++p;
			s[i] = c[s[i] - '0'];
		}
		return s;
	};
	map dp{ pair(string(n - 1, '0') + "1", 1) };
	for (int iter = 0; iter < m; iter++) {
		for (int i = 0; i < n; i++) {
			if (iter == 0 && i == 0) continue;
			map ndp{ pair(string(0, 0), 0) };
			ndp.clear();
			auto update = [&](string s, int val) {
				s = conv(s);
				if (s.find('1') == -1) return;
				ndp[s] += val;
				if (ndp[s] >= mod) ndp[s] -= mod;
			};
			for (auto [s, val] : dp) {
				string ns = s.substr(1);
				ns.push_back('0');
				update(ns, val);
				ns.pop_back();
				char v1 = '5';
				char v2 = '5';
				if (s[0] != '0') v1 = s[0];
				if (i > 0 && s[n - 1] != '0') v2 = s[n - 1];
				if (v1 > v2) swap(v1, v2);
				for (char& c : ns) if (c == v2) c = v1;
				ns.push_back(v1);
				update(ns, val);
			}
			dp.swap(ndp);
		}
	}
	int ret = 0;
	for (auto [s, val] : dp) {
		if (s[n - 1] != '1') continue;
		ret += val;
		if (ret >= mod) ret -= mod;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << sol(n, m) << '\n';
}