#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, string s) {
	i64 ret = 0;
	vector psum(n + 1, n);
	vector prv(2 * n + 1, -1);
	prv[n] = 0;
	for (int i = 1; i <= n; i++) {
		psum[i] = psum[i - 1] + (s[i - 1] == '1' ? 1 : -1);
		if (prv[psum[i]] == -1) ret += i64(i) * (n - i + 1);
		else ret += i64(i - prv[psum[i]] - 1) * (n - i + 1);
		prv[psum[i]] = i;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	cout << sol(n, s) << '\n';
}