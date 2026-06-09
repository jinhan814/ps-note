#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	if (n == 1) return v[0] != 1;
	sort(v.begin(), v.end(), greater{});
	if (v[n - 2] == 0) return true;
	bool flag = v[n - 1] == 0;
	if (flag) v.pop_back();
	int acc = 0;
	while (v.size()) {
		if (v.back() - acc >= 2) return !flag;
		if (v.size() >= 2 && v[v.size() - 2] - acc == 1) return flag;
		v.pop_back();
		acc++;
	}
	return flag;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << (sol(n, v) ? "Alice" : "Bob") << '\n';
	}
}