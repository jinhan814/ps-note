#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int l, int r, string s) {
	vector psum(n + 1, vector(26, 0));
	for (int i = 0; i < n; i++) {
		psum[i + 1] = psum[i];
		psum[i + 1][s[i] - 'a']++;
	}
	i64 ret = 0;
	for (int i = 0; i + l < n; i++) {
		int v1 = psum[min(i + r + 1, n)][s[i] - 'a'];
		int v2 = psum[i + l][s[i] - 'a'];
		ret += v1 - v2;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, l, r; cin >> n >> l >> r;
	string s; cin >> s;
	cout << sol(n, l, r, s) << '\n';
}