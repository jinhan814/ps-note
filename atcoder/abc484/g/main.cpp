#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s, string a, string b) {
	vector nxt(0, array{ -1, -1 });
	vector c(1 << a.size(), vector(1 << b.size(), -1)); c[1][1] = 0;
	vector v(1, pair(1, 1));
	for (int iter = 0; iter < v.size(); iter++) {
		auto [s1, s2] = v[iter];
		nxt.push_back(array{ 0, 0 });
		for (int x = 0; x <= 1; x++) {
			int ns1 = 0, ns2 = 0;
			for (int i = 0; i < a.size(); i++) {
				if (~s1 >> i & 1) continue;
				if (a[i] == 49 - x) continue;
				if (i + 1 < a.size()) ns1 |= 1 << (i + 1);
				else ns1 |= 1, ns2 |= 1;
			}
			for (int i = 0; i < b.size(); i++) {
				if (~s2 >> i & 1) continue;
				if (b[i] == 49 - x) continue;
				if (i + 1 < b.size()) ns2 |= 1 << (i + 1);
				else ns1 |= 1;
			}
			if (c[ns1][ns2] == -1) {
				c[ns1][ns2] = v.size();
				v.push_back(pair(ns1, ns2));
			}
			nxt[iter][x] = c[ns1][ns2];
		}
	}
	vector dp(v.size(), 0); dp[0] = 1;
	for (char c : s) {
		vector ndp(v.size(), 0);
		for (int i = 0; i < v.size(); i++) {
			if (c != '1') ndp[nxt[i][0]] = add(ndp[nxt[i][0]], dp[i]);
			if (c != '0') ndp[nxt[i][1]] = add(ndp[nxt[i][1]], dp[i]);
		}
		dp.swap(ndp);
	}
	int ret = 0;
	for (int i = 0; i < v.size(); i++) {
		auto [s1, s2] = v[i];
		if ((s1 | s2) & 1) ret = add(ret, dp[i]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, a, b; cin >> s >> a >> b;
	cout << sol(s, a, b) << '\n';
}