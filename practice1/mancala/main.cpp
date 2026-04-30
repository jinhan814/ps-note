#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n) {
	vector v(101, 0); v[0] = n;
	while (v[0] > 0) {
		int i = 1;
		while (v[i] != 0) i++;
		v[i] = i;
		for (int j = 0; j < i; j++) v[j]--;
	}
	while (v.back() == 0) v.pop_back();
	v.erase(v.begin());
	return v;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int x, n; cin >> x >> n;
        assert(n <= 2000);
		auto res = sol(n);
		cout << x << ' ' << res.size() << '\n';
		for (int i = 0; i < res.size(); i += 10) {
			for (int j = 0; j < 10; j++) {
				if (i + j == res.size()) break;
				if (j) cout << ' ';
				cout << res[i + j];
			}
			cout << '\n';
		}
	}
}