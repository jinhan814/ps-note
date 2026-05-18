#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 998'244'353;

constexpr int add(int a, int b) {
	return a + b < mod ? a + b : a + b - mod;
}

constexpr int mul(int a, int b) {
	return i64(a) * b % mod; 
}

auto matmul = [](auto a, auto b) {
	int n = a.size();
	vector ret(n, vector(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				int val = mul(a[i][k], b[k][j]);
				ret[i][j] = add(ret[i][j], val);
			}
		}
	}
	return ret;
};

auto matpow = [](auto a, int k) {
	int n = a.size();
	vector ret(n, vector(n, 0));
	for (int i = 0; i < n; i++) ret[i][i] = 1;
	for (; k; k >>= 1) {
		if (k & 1) ret = matmul(ret, a);
		a = matmul(a, a);
	}
	return ret;
};

auto sol = [](int n, int m, auto v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	auto f = [&](string s) {
		for (int i = 0; i < v.size(); i++) {
			if (s.size() < v[i].size()) continue;
			if (s.substr(s.size() - v[i].size()) != v[i]) continue;
			return true;
		}
		return false;
	};
	vector c(1, string(0, 0));
	for (int i = 0; i < v.size(); i++) {
		string s;
		for (char x : v[i]) {
			s.push_back(x);
			if (!f(s)) c.push_back(s);
		}
	}
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector d(c.size(), vector(c.size(), 0));
	for (int i = 0; i < c.size(); i++) {
		for (char x = 'a'; x <= 'z'; x++) {
			string s = c[i] + x;
			if (f(s)) continue;
			while (!binary_search(c.begin(), c.end(), s)) s.erase(s.begin());
			auto it = lower_bound(c.begin(), c.end(), s);
			assert(it != c.end() && *it == s);
			d[i][it - c.begin()]++;
		}
	}
	d = matpow(d, n);
	int ret = 0;
	for (int i = 0; i < c.size(); i++) ret = add(ret, d[0][i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, string(0, 0));
	for (int i = 0; i < m; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}