#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto calc = [](int n, string a, string b, string c) {
	vector p1(n + 1, 0), p2(n + 1, 0), p3(n + 1, 0);
	for (int i = 0; i < n; i++) {
		p1[i + 1] = p1[i] + (a[i] == '.');
		p2[i + 1] = p2[i] + (b[i] == '.');
		p3[i + 1] = p3[i] + (c[i] == '.');
	}
	i64 ret = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		if (c[i - 1] == '#') continue;
		if (j < i) j = i;
		while (j <= n && (p1[j] == p1[i - 1] || p2[j] == p2[i - 1])) j++;
		ret += p3[n] - p3[j - 1];
	}
	return ret;
};

auto sol = [](int n, int m, auto v) {
	if (n > m) {
		vector c(m, string(n, '.'));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) c[j][i] = v[i][j];
		}
		swap(n, m);
		v.swap(c);
	}
	i64 ret = 1;
	for (int i = 0; i < n; i++) {
		string c(m, '#');
		for (int j = i; j < n; j++) {
			for (int k = 0; k < m; k++) {
				if (v[j][k] == '#') continue;
				c[k] = '.';
			}
			ret += calc(m, v[i], v[j], c);
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}