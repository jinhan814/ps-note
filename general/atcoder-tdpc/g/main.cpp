#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](string s, i64 k) {
	vector dp(s.size(), i64(0));
	vector nxt(s.size(), vector(26, 0));
	vector c(26, i64(0));
	vector p(26, -1);
	i64 acc = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		i64 val = c[s[i] - 'a'];
		c[s[i] - 'a'] = min(acc + 1, i64(1e18));
		acc = min(acc - val + c[s[i] - 'a'], i64(1e18));
		dp[i] = c[s[i] - 'a'];
		nxt[i] = p;
		p[s[i] - 'a'] = i;
	}
	if (acc < k) return string("Eel");
	string ret;
	int pos = -1;
	for (int i = 0; i < 26; i++) {
		if (p[i] == -1) continue;
		if (k <= c[i]) {
			ret.push_back('a' + i);
			pos = p[i];
			break;
		}
		else {
			k -= c[i];
		}
	}
	while (k > 1) {
		k--;
		for (int i = 0; i < 26; i++) {
			if (nxt[pos][i] == -1) continue;
			if (k <= dp[nxt[pos][i]]) {
				ret.push_back('a' + i);
				pos = nxt[pos][i];
				break;
			}
			else {
				k -= dp[nxt[pos][i]];
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	i64 k; cin >> k;
	cout << sol(s, k) << '\n';
}