#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	set s(v.begin(), v.end());
	while (*s.begin() + k <= *prev(s.end())) {
		int x = *prev(s.end()) - *s.begin();
		s.insert(*s.begin() + x / k * k);
		s.erase(s.begin());
	}
	int ret = 1 << 30;
	for (int iter = 0; iter < s.size(); iter++) {
		ret = min(ret, *prev(s.end()) - *s.begin());
		s.insert(*s.begin() + k);
		s.erase(s.begin());
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}