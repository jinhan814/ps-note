#include <bits/stdc++.h>
using namespace std;

auto sol1 = [](int n, int k, auto v1, auto v2) {
	vector p1(v1.size() + 1, 0);
	vector p2(v2.size() + 1, 0);
	for (int i = v1.size() - 1; i >= 0; i--) p1[i] = v1[i].second + p1[i + 1];
	for (int i = v2.size() - 1; i >= 0; i--) p2[i] = v2[i].second + p2[i + 1];
	vector dp(v1.size(), vector(v2.size(), -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == v1.size()) return p2[j];
		if (j == v2.size()) return p1[i];
		int& ret = dp[i][j];
		if (ret != -1) return ret;
		ret = 1 << 30;
		if (abs(v1[i].first - v2[j].first) <= k) ret = min(ret, self(self, i + 1, j + 1));
		ret = min(ret, self(self, i + 1, j) + v1[i].second);
		ret = min(ret, self(self, i, j + 1) + v2[j].second);
		return ret;
	};
	return rec(rec, 0, 0);
};

auto sol2 = [](int n, int k, auto v1, auto v2) {
	vector p1(v1.size() + 1, 0);
	for (int i = v1.size() - 1; i >= 0; i--) {
		p1[i] = v1[i].second + p1[i + 1];
	}
	vector p2(v2.size() + 1, 0);
	for (int i = v2.size() - 1; i >= 0; i--) {
		p2[i] = v2[i].second + p2[i + 1];
	}
	vector c1(v1.size(), 0);
	for (int i = 0, p = -1; i < v1.size(); i++) {
		int pos = i > 0 ? v1[i - 1].first : -(1 << 30);
		while (p + 1 < v2.size() && v2[p + 1].first <= pos + k) p++;
		c1[i] = p;
	}
	vector c2(v2.size(), 0);
	for (int i = 0, p = -1; i < v2.size(); i++) {
		int pos = i > 0 ? v2[i - 1].first : -(1 << 30);
		while (p + 1 < v1.size() && v1[p + 1].first <= pos + k) p++;
		c2[i] = p;
	}
	vector d(v1.size(), vector(v2.size(), 0));
	for (int i = v1.size() - 1; i >= 0; i--) {
		for (int j = v2.size() - 1; j >= 0; j--) {
			if (abs(v1[i].first - v2[j].first) > k) continue;
			d[i][j] = 1;
			if (i + 1 < v1.size() && j + 1 < v2.size()) d[i][j] += d[i + 1][j + 1];
		}
	}
	vector dp(v1.size(), vector(v2.size(), array{ -1, -1, -1 }));
	auto rec = [&](const auto& self, int i, int j, int f) -> int {
		if (f == 1) {
			int pos = i > 0 ? v1[i - 1].first : -(1 << 30);
			if (j < v2.size() && v2[j].first > pos + k) f = 0;
		}
		if (f == 2) {
			int pos = j > 0 ? v2[j - 1].first : -(1 << 30);
			if (i < v1.size() && v1[i].first > pos + k) f = 0;
		}
		if (f == 0) {
			if (i >= v1.size()) return p2[j];
			if (j >= v2.size()) return p1[i];
			int& ret = dp[i][j][f];
			if (ret != -1) return ret;
			ret = -(1 << 30);
			ret = max(ret, self(self, i + 1, j, 1) + v1[i].second);
			ret = max(ret, self(self, i, j + 1, 2) + v2[j].second);
			if (abs(v1[i].first - v2[j].first) <= k) {
				ret = max(ret, self(self, i + 1, j + 1, 0));
			}
			return ret;
		}
		else if (f == 1) {
			if (j >= v2.size()) return p1[i];
			if (i >= v1.size()) return -(1 << 30);
			int& ret = dp[i][j][f];
			if (ret != -1) return ret;
			ret = -(1 << 30);
			ret = max(ret, self(self, i + 1, j, 1) + v1[i].second);
			if (abs(v1[i].first - v2[j].first) <= k) {
				ret = max(ret, self(self, i + 1, j + 1, 1));
			}
			int cnt = c1[i] - j + 1;
			if (d[i][j] >= cnt) {
				ret = max(ret, self(self, i + cnt, j + cnt, 0));
			}
			return ret;
		}
		else {
			if (i >= v1.size()) return p2[j];
			if (j >= v2.size()) return -(1 << 30);
			int& ret = dp[i][j][f];
			if (ret != -1) return ret;
			ret = -(1 << 30);
			ret = max(ret, self(self, i, j + 1, 2) + v2[j].second);
			if (abs(v1[i].first - v2[j].first) <= k) {
				ret = max(ret, self(self, i + 1, j + 1, 2));
			}
			int cnt = c2[j] - i + 1;
			if (d[i][j] >= cnt) {
				ret = max(ret, self(self, i + cnt, j + cnt, 0));
			}
			return ret;
		}
	};
	return rec(rec, 0, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int type; cin >> type;
	int n, k; cin >> n >> k;
	vector v1(0, pair(0, 0));
	vector v2(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		char c; cin >> c;
		int a, b; cin >> a >>b;
		if (c == 'H') v1.push_back(pair(a, b));
		else v2.push_back(pair(a, b));
	}
	if (type == 1) cout << sol1(n, k, v1, v2) << '\n';
	else cout << sol2(n, k, v1, v2) << '\n';
}