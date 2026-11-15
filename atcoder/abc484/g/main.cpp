#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](string s, string a, string b) {
	int sz = max(a.size(), b.size());
	vector p(sz + 1, 1);
	for (int i = 1; i <= sz; i++) p[i] = p[i - 1] * 3;
	vector c(p[sz] << sz, -1); c[1 << sz] = 0;
	vector v(1, pair(0, 1));
	vector nxt(0, array{ 0, 0 });
	for (int iter = 0; iter < v.size(); iter++) {
		auto [s1, s2] = v[iter];
		nxt.push_back(array{ 0, 0 });
		for (int x = 0; x <= 1; x++) {
			int ns1 = ((s1 << 1) & ((1 << sz) - 1)) | x;
			int ns2 = s2 * 3 % p[sz];
			if (s2 / p[a.size() - 1] % 3 != 0) {
				bool flag = true;
				for (int i = 0; i < a.size(); i++) {
					if (a[i] == '?') continue;
					if ((ns1 >> (a.size() - i - 1) & 1) == a[i] - 48) continue;
					flag = false;
					break;
				}
				if (flag) ns2++;
			}
			if (s2 / p[b.size() - 1] % 3 == 1 && ns2 % 3 == 0) {
				bool flag = true;
				for (int i = 0; i < b.size(); i++) {
					if (b[i] == '?') continue;
					if ((ns1 >> (b.size() - i - 1) & 1) == b[i] - 48) continue;
					flag = false;
					break;
				}
				if (flag) ns2 += 2;
			}
			if (c[ns1 | ns2 << sz] == -1) {
				c[ns1 | ns2 << sz] = v.size();
				v.push_back(pair(ns1, ns2));
			}
			nxt[iter][x] = c[ns1 | ns2 << sz];
		}
	}
	vector dp(v.size(), 0);
	for (int i = 0; i < v.size(); i++) {
		auto [s1, s2] = v[i];
		if (s2 % 3 != 0) dp[i] = 1;
	}
	for (int iter = s.size() - 1; iter >= 0; iter--) {
		vector ndp(v.size(), 0);
		for (int i = 0; i < v.size(); i++) {
			if (s[iter] != '1') ndp[i] = add(ndp[i], dp[nxt[i][0]]);
			if (s[iter] != '0') ndp[i] = add(ndp[i], dp[nxt[i][1]]);
		}
		dp.swap(ndp);
	}
	return dp[0];
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, a, b; cin >> s >> a >> b;
	cout << sol(s, a, b) << '\n';
}