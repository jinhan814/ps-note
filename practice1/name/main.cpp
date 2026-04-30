#include <bits/stdc++.h>
using namespace std;

auto sol_0 = [](int n, int m, string a, string b) {
	vector dp(n + 1, vector(m + 1, -1));
	auto rec = [&](const auto& self, int i, int j) -> int {
		if (i == 0) return j;
		if (j == 0) return i;
		int& ret = dp[i][j];
		if (ret != -1) return ret;
		if (a[i - 1] == b[j - 1]) return ret = self(self, i - 1, j - 1) + 1;
		return ret = min(self(self, i - 1, j), self(self, i, j - 1)) + 1;
	};
	return rec(rec, n, m);
};

auto sol_1 = [](int n, int m, string a, string b) {
	vector dp(n + 1, vector(m + 1, vector(3, -1)));
	auto rec = [&](const auto& self, int i, int j, int p) -> int {
		if (i == 0 && j == 0) return 0;
		int k;
		if (i > 0 && a[i - 1] == p) k = 0;
		else if (j > 0 && b[j - 1] == p) k = 1;
		else k = 2;
		int& ret = dp[i][j][k];
		if (ret != -1) return ret;
		ret = 1 << 30;
		if (i == 0) {
			int res = self(self, i, j - 1, b[j - 1]) + 1;
			if (b[j - 1] == p) res++;
			ret = min(ret, res);
		}
		else if (j == 0) {
			int res = self(self, i - 1, j, a[i - 1]) + 1;
			if (a[i - 1] == p) res++;
			ret = min(ret, res);
		}
		else {
			if (a[i - 1] == b[j - 1]) {
				int res = self(self, i - 1, j - 1, a[i - 1]) + 1;
				if (a[i - 1] == p) res++;
				ret = min(ret, res);
			}
			else {
				int r1 = self(self, i - 1, j, a[i - 1]) + 1;
				if (a[i - 1] == p) r1++;
				int r2 = self(self, i, j - 1, b[j - 1]) + 1;
				if (b[j - 1] == p) r2++;
				ret = min(ret, min(r1, r2));
			}
		}
		return ret;
	};
	return rec(rec, n, m, 52);
};

auto sol_2 = [](int n, int m, string a, string b) {
	vector dp(n + 1, vector(m + 1, vector(5 * 5, -1)));
	auto f = [](int x, int p1, int p2) {
		if (x == p1 || x == p2) return 52;
		return p1;
	};
	auto rec = [&](const auto& self, int i, int j, int p1, int p2) -> int {
		if (i == 0 && j == 0) return 0;
		int k1;
		if (i > 0 && a[i - 1] == p1) k1 = 0;
		else if (i > 1 && a[i - 2] == p1) k1 = 1;
		else if (j > 0 && b[j - 1] == p1) k1 = 2;
		else if (j > 1 && b[j - 2] == p1) k1 = 3;
		else k1 = 4;
		int k2;
		if (i > 0 && a[i - 1] == p2) k2 = 0;
		else if (i > 1 && a[i - 2] == p2) k2 = 1;
		else if (j > 0 && b[j - 1] == p2) k2 = 2;
		else if (j > 1 && b[j - 2] == p2) k2 = 3;
		else k2 = 4;
		int& ret = dp[i][j][5 * k1 + k2];
		if (ret != -1) return ret;
		ret = 1 << 30;
		if (i == 0) {
			int res = self(self, i, j - 1, b[j - 1], f(b[j - 1], p1, p2)) + 1;
			if (b[j - 1] == p1) res += 2;
			if (b[j - 1] == p2) res++;
			ret = min(ret, res);
		}
		else if (j == 0) {
			int res = self(self, i - 1, j, a[i - 1], f(a[i - 1], p1, p2)) + 1;
			if (a[i - 1] == p1) res += 2;
			if (a[i - 1] == p2) res++;
			ret = min(ret, res);
		}
		else {
			if (a[i - 1] == b[j - 1]) {
				int res = self(self, i - 1, j - 1, a[i - 1], f(a[i - 1], p1, p2)) + 1;
				if (a[i - 1] == p1) res += 2;
				if (a[i - 1] == p2) res++;
				ret = min(ret, res);
			}
			else {
				int r1 = self(self, i - 1, j, a[i - 1], f(a[i - 1], p1, p2)) + 1;
				if (a[i - 1] == p1) r1 += 2;
				if (a[i - 1] == p2) r1++;
				int r2 = self(self, i, j - 1, b[j - 1], f(b[j - 1], p1, p2)) + 1;
				if (b[j - 1] == p1) r2 += 2;
				if (b[j - 1] == p2) r2++;
				ret = min(ret, min(r1, r2));
			}
		}
		return ret;
	};
	return rec(rec, n, m, 52, 52);
};

auto sol_3 = [](int n, int m, string a, string b) {
	vector dp(n + 1, vector(m + 1, vector(7 * 7 * 7, -1)));
	auto f = [](int x, int p1, int p2, int p3) {
		if (x == p1 || x == p2 || x == p3) return 52;
		return p1;
	};
	auto g = [](int x, int p1, int p2, int p3) {
		if (x == p1 || x == p2) return 52;
		if (x == p3) return p1;
		return p2;
	};
	auto rec = [&](const auto& self, int i, int j, int p1, int p2, int p3) -> int {
		if (i == 0 && j == 0) return 0;
		int k1;
		if (i > 0 && a[i - 1] == p1) k1 = 0;
		else if (j > 0 && b[j - 1] == p1) k1 = 1;
		else if (i > 1 && a[i - 2] == p1) k1 = 2;
		else if (j > 1 && b[j - 2] == p1) k1 = 3;
		else if (i > 2 && a[i - 3] == p1) k1 = 4;
		else if (j > 2 && b[j - 3] == p1) k1 = 5;
		else k1 = 6;
		int k2;
		if (i > 0 && a[i - 1] == p2) k2 = 0;
		else if (j > 0 && b[j - 1] == p2) k2 = 1;
		else if (i > 1 && a[i - 2] == p2) k2 = 2;
		else if (j > 1 && b[j - 2] == p2) k2 = 3;
		else if (i > 2 && a[i - 3] == p2) k2 = 4;
		else if (j > 2 && b[j - 3] == p2) k2 = 5;
		else k2 = 6;
		int k3;
		if (i > 0 && a[i - 1] == p3) k3 = 0;
		else if (j > 0 && b[j - 1] == p3) k3 = 1;
		else if (i > 1 && a[i - 2] == p3) k3 = 2;
		else if (j > 1 && b[j - 2] == p3) k3 = 3;
		else if (i > 2 && a[i - 3] == p3) k3 = 4;
		else if (j > 2 && b[j - 3] == p3) k3 = 5;
		else k3 = 6;
		int& ret = dp[i][j][49 * k1 + 7 * k2 + k3];
		if (ret != -1) return ret;
		ret = 1 << 30;
		if (i == 0) {
			int res = self(self, i, j - 1, b[j - 1], f(b[j - 1], p1, p2, p3), g(b[j - 1], p1, p2, p3)) + 1;
			if (b[j - 1] == p1) res += 3;
			if (b[j - 1] == p2) res += 2;
			if (b[j - 1] == p3) res++;
			ret = min(ret, res);
		}
		else if (j == 0) {
			int res = self(self, i - 1, j, a[i - 1], f(a[i - 1], p1, p2, p3), g(a[i - 1], p1, p2, p3)) + 1;
			if (a[i - 1] == p1) res += 3;
			if (a[i - 1] == p2) res += 2;
			if (a[i - 1] == p3) res++;
			ret = min(ret, res);
		}
		else {
			if (a[i - 1] == b[j - 1]) {
				int res = self(self, i - 1, j - 1, a[i - 1], f(a[i - 1], p1, p2, p3), g(a[i - 1], p1, p2, p3)) + 1;
				if (a[i - 1] == p1) res += 3;
				if (a[i - 1] == p2) res += 2;
				if (a[i - 1] == p3) res++;
				ret = min(ret, res);
			}
			else {
				int r1 = self(self, i - 1, j, a[i - 1], f(a[i - 1], p1, p2, p3), g(a[i - 1], p1, p2, p3)) + 1;
				if (a[i - 1] == p1) r1 += 3;
				if (a[i - 1] == p2) r1 += 2;
				if (a[i - 1] == p3) r1++;
				int r2 = self(self, i, j - 1, b[j - 1], f(b[j - 1], p1, p2, p3), g(b[j - 1], p1, p2, p3)) + 1;
				if (b[j - 1] == p1) r2 += 3;
				if (b[j - 1] == p2) r2 += 2;
				if (b[j - 1] == p3) r2++;
				ret = min(ret, min(r1, r2));
			}
		}
		return ret;
	};
	return rec(rec, n, m, 52, 52, 52);
};

auto sol = [](int n, int m, int k, string a, string b) {
	for (char& c : a) c = c >= 'a' ? c - 'a' : c - 'A' + 26;
	for (char& c : b) c = c >= 'a' ? c - 'a' : c - 'A' + 26;
	if (k == 0) return sol_0(n, m, a, b);
	if (k == 1) return sol_1(n, m, a, b);
	if (k == 2) return sol_2(n, m, a, b);
	if (k == 3) return sol_3(n, m, a, b);
	assert(0);
	return -1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	string a, b; cin >> a >> b;
	cout << sol(n, m, k, a, b) << '\n';
}