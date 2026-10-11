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

auto sol = [](int n, auto v) {
	int ret = 1;
	vector c(1, 0);
	for (int i = 1; i < n; i++) {
		while (c.size() > 1 && v[c.back()] < v[i]) c.pop_back();
		ret = mul(ret, i - c.back());
		c.push_back(i);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}