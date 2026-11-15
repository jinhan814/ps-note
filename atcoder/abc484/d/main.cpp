#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	i64 ret = 1;
	vector c(n + 1, 0);
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		ret += i - c[v[i]];
		c[v[i]] += j - i;
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