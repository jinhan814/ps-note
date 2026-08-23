#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	i64 ret = 0;
	int x = 0;
	set s(v.begin(), v.end());
	while (s.size()) {
		auto it = s.lower_bound(x);
		if (it == s.end()) it--;
		if (it != s.begin() && x - *prev(it) <= *it - x) it--;
		ret += abs(*it - x);
		x = *it;
		s.erase(it);
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