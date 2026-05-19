#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(n, -1);
	vector s(0, 0);
	for (int i = 0; i < n; i++) {
		int p = -1;
		while (s.size() && v[s.back()] > v[i]) {
			p = s.back();
			s.pop_back();
		}
		if (s.size()) ret[i] = s.back();
		if (p != -1) ret[p] = i;
		s.push_back(i);
	}
	for (int i = 0; i < n; i++) {
		if (ret[i] != -1) continue;
		ret[i] = i;
		break;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int i = 0; i < n; i++) cout << res[i] << ' ';
	cout << '\n';
}