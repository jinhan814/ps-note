#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		if (v[i] == 0) continue;
		if (j - i != 2) return true;
	}
	return false;
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