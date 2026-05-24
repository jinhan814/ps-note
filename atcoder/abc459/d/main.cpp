#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	vector cnt(26, 0);
	for (char c : s) cnt[c - 'a']++;
	vector cand(26, 0);
	iota(cand.begin(), cand.end(), 0);
	sort(cand.begin(), cand.end(), [&](int i, int j) {
		return cnt[i] > cnt[j];
	});
	if (cnt[cand[0]] > (s.size() + 1) / 2) return string(0, 0);
	string ret(s.size(), 0);
	int p = 0;
	for (int i : cand) {
		for (int iter = 0; iter < cnt[i]; iter++) {
			ret[p] = 'a' + i;
			p += 2;
			if (p >= s.size()) p = 1;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		string s; cin >> s;
		auto res = sol(s);
		if (res.size()) {
			cout << "Yes" << '\n';
			cout << res << '\n';
		}
		else {
			cout << "No" << '\n';
		}
	}
}