#include <bits/stdc++.h>
using namespace std;

auto sol = [](string a, string b) {
	vector dp(a.size(), vector(b.size(), -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i < 0 || j < 0) return 0;
		int& ret = dp[i][j];
		if (ret != -1) return ret;
		ret = -(1 << 30);
		ret = max(ret, self(self, i - 1, j));
		ret = max(ret, self(self, i, j - 1));
		if (a[i] == b[j]) ret = max(ret, self(self, i - 1, j - 1) + 1);
		return ret;
	};
	string ret;
	auto trace = [&](const auto& self, int i, int j) -> void {
		if (i < 0 || j < 0) return;
		int val = rec(rec, i, j);
		if (rec(rec, i - 1, j) == val) {
			self(self, i - 1, j);
		}
		else if (rec(rec, i, j - 1) == val) {
			self(self, i, j - 1);
		}
		else {
			self(self, i - 1, j - 1);
			ret.push_back(a[i]);
		}
	};
	trace(trace, a.size() - 1, b.size() - 1);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a, b; cin >> a >> b;
	cout << sol(a, b) << '\n';
}