#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 835'454'957;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

auto sol = [](int n, int lim, auto v) {
	vector rv = v;
	for (int i = 0; i < n; i++) reverse(rv[i].begin(), rv[i].end());
	vector dp(lim + 1, vector(n, vector(16, vector(2, -1))));
	auto rec = [&](const auto& self, int len, int i, int j, int f) -> int {
		int& ret = dp[len][i][j][f];
		if (ret != -1) return ret;
		ret = 0;
		{
			bool flag = true;
			if (f) swap(v, rv);
			for (int p = 0; p < j; p++) {
				char v1 = v[i][v[i].size() - j + p];
				char v2 = v[i][v[i].size() - 1 - p];
				if (v1 != v2) flag = false;
			}
			if (f) swap(v, rv);
			if (flag) ret = add(ret, 1);
		}
		for (int k = 0; k < n; k++) {
			int nlen = len + v[k].size() + 1;
			if (nlen > lim) continue;
			bool flag = true;
			if (f) swap(v, rv);
			for (int p = 0; p < j && p < v[k].size(); p++) {
				char v1 = v[i][v[i].size() - j + p];
				char v2 = v[k][v[k].size() - 1 - p];
				if (v1 != v2) flag = false;
			}
			if (f) swap(v, rv);
			if (!flag) continue;
			if (v[k].size() < j) {
				int res = self(self, nlen, i, j - v[k].size(), f);
				ret = add(ret, res);
			}
			else if (v[k].size() == j) {
				int res = self(self, nlen, 0, 0, 0);
				ret = add(ret, res);
			}
			else {
				int res = self(self, nlen, k, v[k].size() - j, !f);
				ret = add(ret, res);
			}
		}
		return ret;
	};
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].size() > lim) continue;
		if (v[i] == rv[i]) ret = add(ret, 1);
		for (int j = 0; j < n; j++) {
			int len = v[i].size() + v[j].size() + 1;
			if (len > lim) continue;
			bool flag = true;
			for (int p = 0; p < v[i].size() && p < v[j].size(); p++) {
				char v1 = v[i][p];
				char v2 = v[j][v[j].size() - 1 - p];
				if (v1 != v2) flag = false;
			}
			if (!flag) continue;
			if (v[i].size() < v[j].size()) {
				int res = rec(rec, len, j, v[j].size() - v[i].size(), 1);
				ret = add(ret, res);
			}
			else if (v[i].size() == v[j].size()) {
				int res = rec(rec, len, 0, 0, 0);
				ret = add(ret, res);
			}
			else {
				int res = rec(rec, len, i, v[i].size() - v[j].size(), 0);
				ret = add(ret, res);
			}
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}