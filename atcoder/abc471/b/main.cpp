#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	map cnt{ pair(string{}, 0) };
	for (string s : v) {
		for (char& c : s) c |= 32;
		cnt[s]++;
	}
	int ret = 0;
	for (auto [a, b] : cnt) ret = max(ret, b);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}