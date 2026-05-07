#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, string a, string b, string c) {
	vector dp(n, vector(a.size() + 1, vector(b.size() + 1, vector(c.size() + 1, -1))));
	auto rec = [&](const auto& self, int len, int i, int j, int k) -> int {
		if (len == n) {
			if (i == a.size()) return 0;
			if (j == b.size()) return 0;
			if (k == c.size()) return 0;
			return 1;
		}
		else {
			int& ret = dp[len][i][j][k];
			if (ret != -1) return ret;
			ret = 0;
			for (char x = 'a'; x <= 'z'; x++) {
				int ni = i, nj = j, nk = k;
				if (i < a.size() && x == a[i]) ni++;
				if (j < b.size() && x == b[j]) nj++;
				if (k < c.size() && x == c[k]) nk++;
				ret = add(ret, self(self, len + 1, ni, nj, nk));
			}
			return ret;
		}
	};
	return rec(rec, 0, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string a, b, c; cin >> a >> b >> c;
	cout << sol(n, a, b, c) << '\n';
}