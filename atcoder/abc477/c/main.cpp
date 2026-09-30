#include <bits/stdc++.h>
using namespace std;

auto sol = [](int q, string s, string t, auto qs) {
	vector psum(s.size() + 1, 0);
	for (int i = 0; i + t.size() <= s.size(); i++) {
		psum[i + 1] = psum[i];
		if (s.substr(i, t.size()) == t) psum[i + 1]++;
	}
	vector ret(q, false);
	for (int i = 0; i < q; i++) {
		auto [l, r] = qs[i];
		if (r - l + 1 < t.size()) continue;
		if (psum[r - t.size() + 1] - psum[l - 1] == 0) continue;
		ret[i] = true;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q; cin >> q;
	string s, t; cin >> s >> t;
	vector qs(q, array{ 0, 0 });
	for (int i = 0; i < q; i++) cin >> qs[i][0] >> qs[i][1];
	auto res = sol(q, s, t, qs);
	for (int i = 0; i < q; i++) cout << (res[i] ? "Yes" : "No") << '\n';
}