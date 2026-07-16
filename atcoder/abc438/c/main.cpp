#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector s(0, 0);
	for (int x : v) {
		s.push_back(x);
		if (s.size() < 4) continue;
		bool flag = true;
		for (int i = 0; i < 4; i++) {
			if (s[s.size() - 1 - i] == s.back()) continue;
			flag = false;
			break;
		}
		if (!flag) continue;
		for (int i = 0; i < 4; i++) s.pop_back();
	}
	return s.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}