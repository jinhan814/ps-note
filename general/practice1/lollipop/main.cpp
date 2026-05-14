#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto qs) {
	vector psum(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		psum[i] = psum[i - 1] + v[i];
	}
	vector cand(1, 1);
	for (int i = 1; i <= n; i++) {
		if (v[i] != 1) continue;
		cand.push_back(i);
		if (i + 1 <= n) cand.push_back(i + 1);
		break;
	}
	for (int i = n; i >= 1; i--) {
		if (v[i] != 1) continue;
		cand.push_back(i);
		if (i - 1 >= 1) cand.push_back(i - 1);
		break;
	}
	sort(cand.begin(), cand.end());
	cand.erase(unique(cand.begin(), cand.end()), cand.end());
	vector d(psum[n] + 1, pair(-1, -1));
	for (int i : cand) {
		for (int j = 1; j <= i; j++) {
			int x = psum[i] - psum[j - 1];
			d[x] = pair(j, i);
		}
		for (int j = i + 1; j <= n; j++) {
			int x = psum[j] - psum[i - 1];
			d[x] = pair(i, j);
		}
	}
	vector ret(q, pair(-1, -1));
	for (int i = 0; i < q; i++) {
		if (qs[i] > psum[n]) continue;
		ret[i] = d[qs[i]];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	string s; cin >> s;
	vector v(n + 1, 0);
	vector qs(q, 0);
	for (int i = 1; i <= n; i++) v[i] = s[i - 1] == 'W' ? 1 : 2;
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, q, v, qs);
	for (auto [a, b] : res) {
		if (a == -1) cout << "NIE" << '\n';
		else cout << a << ' ' << b << '\n';
	}
}