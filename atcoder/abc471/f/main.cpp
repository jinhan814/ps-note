#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, auto v) {
	auto conv = [](string s) {
		reverse(s.begin(), s.end());
		while (s.size() && s.back() == '0') s.pop_back();
		if (s.empty()) s.push_back('0');
		reverse(s.begin(), s.end());
		return s;
	};
	auto cmp = [](string a, string b) {
		if (a.size() != b.size()) return a.size() > b.size();
		return a > b;
	};
	sort(v.begin(), v.end(), cmp);
	sort(v.begin(), v.begin() + k, [](string a, string b) { return a + b > b + a; });
	string ret;
	for (int i = 0; i < k; i++) ret += v[i];
	ret = conv(ret);
	if (v.size() > k) {
		int p = 0;
		for (int i = 1; i < k; i++) if (cmp(v[p], v[i])) p = i;
		for (int i = k; i < n; i++) v[i] = conv(v[i]);
		string res = v[k];
		for (int i = k + 1; i < n; i++) if (cmp(v[i], res)) res = v[i];
		for (int i = 0; i < p; i++) res += v[i];
		for (int i = p + 1; i < k; i++) res += v[i];
		res = conv(res);
		if (cmp(res, ret)) ret = res;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, k, v) << '\n';
}