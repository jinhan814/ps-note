#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	map<int, int> cnt;
	for (int x : v) cnt[x]++;
	vector c(0, i64(0));
	for (auto [a, b] : cnt) c.push_back(i64(a) * b);
	sort(c.begin(), c.end());
	while (c.size() && k > 0) c.pop_back(), k--;
	i64 ret = 0;
	for (i64 x : c) ret += x;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}