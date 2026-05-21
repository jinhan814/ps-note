#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n) {
	vector ret(0, i64(0));
	for (i64 i = 1; i <= n; i = n / (n / i) + 1) ret.push_back(n / i);
	reverse(ret.begin(), ret.end());
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	auto res = sol(n);
	cout << res.size() << '\n';
	for (i64 x : res) cout << x << ' ';
	cout << '\n';
}