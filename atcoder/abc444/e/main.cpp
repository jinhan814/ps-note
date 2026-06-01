#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v) {
	i64 ret = 0;
	set s{ 0 }; s.clear();
	for (int i = 0, j = 0; i < n; i++) {
		while (j < n) {
			auto it = s.lower_bound(v[j]);
			if (it != s.end() && *it - v[j] < m) break;
			if (it != s.begin() && v[j] - *prev(it) < m) break;
			s.insert(v[j]);
			j++;
		}
		ret += j - i;
		s.erase(v[i]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, v) << '\n';
}