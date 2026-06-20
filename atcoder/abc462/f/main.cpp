#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s, int k) {
	for (int i = 0; i < s.size(); i++) {
		s[i] -= 65;
		if (s[i] > 3) s[i] = 3;
	}
	vector dp(k + 1, vector(4, vector(4, 1 << 30)));
	for (int c1 = 0; c1 < 4; c1++) {
		for (int c2 = 0; c2 < 4; c2++) {
			int val = 0;
			if (s[0] != c1) val++;
			if (s[1] != c2) val++;
			dp[0][c1][c2] = val;
		}
	}
	for (int i = 2; i < s.size(); i++) {
		vector ndp(k + 1, vector(4, vector(4, 1 << 30)));
		for (int j = 0; j <= k; j++) {
			for (int c1 = 0; c1 < 4; c1++) {
				for (int c2 = 0; c2 < 4; c2++) {
					if (dp[j][c1][c2] == 1 << 30) continue;
					for (int c3 = 0; c3 < 4; c3++) {
						int nj = j;
						if (s[i - 2] == 0 && s[i - 1] == 1 && s[i] == 2) nj--;
						if (c1 == 0 && c2 == 1 && c3 == 2) nj++;
						if (nj < 0 || nj > k) continue;
						int val = dp[j][c1][c2];
						if (s[i] != c3) val++;
						ndp[nj][c2][c3] = min(ndp[nj][c2][c3], val);
					}
				}
			}
		}
		dp.swap(ndp);
	}
	int ret = 1 << 30;
	for (int c1 = 0; c1 < 4; c1++) {
		for (int c2 = 0; c2 < 4; c2++) {
			int val = dp[k][c1][c2];
			ret = min(ret, val);
		}
	}
	if (ret == 1 << 30) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string s; cin >> s;
		int k; cin >> k;
		cout << sol(s, k) << '\n';
	}
}