#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, string s) {
	vector p(3, vector(n + 1, 0));
	for (int i = 0; i < n; i++) {
		p[0][i + 1] = p[0][i];
		p[1][i + 1] = p[1][i];
		p[2][i + 1] = p[2][i];
		p[s[i] - 'A'][i + 1]++;
	}
	i64 ret = i64(n) * (n + 1) / 2;
	map<int, int> c01, c02, c12;
	map<pair<int, int>, int> c012;
	for (int i = 1; i <= n; i++) {
		c01[p[0][i - 1] - p[1][i - 1]]++;
		c02[p[0][i - 1] - p[2][i - 1]]++;
		c12[p[1][i - 1] - p[2][i - 1]]++;
		c012[pair(p[0][i - 1] - p[1][i - 1], p[0][i - 1] - p[2][i - 1])]++;
		ret -= c01[p[0][i] - p[1][i]];
		ret -= c02[p[0][i] - p[2][i]];
		ret -= c12[p[1][i] - p[2][i]];
		ret += 2 * c012[pair(p[0][i] - p[1][i], p[0][i] - p[2][i])];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}