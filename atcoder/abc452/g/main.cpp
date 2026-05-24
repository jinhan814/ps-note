#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto get_sa = [](string s) {
	int n = s.size(), m = max(256, n) + 1;
	vector sa(n, 0), r(n << 1, 0), nr(n << 1, 0);
	vector idx(n, 0), cnt(m, 0);
	for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
	for (int d = 1; d < n; d <<= 1) {
		auto cmp = [&](int a, int b) {
			if (r[a] < r[b]) return true;
			if (r[a] == r[b] && r[a + d] < r[b + d]) return true;
			return false;
		};
		for (int i = 0; i < m; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) cnt[r[i + d]]++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) idx[--cnt[r[i + d]]] = i;
		for (int i = 0; i < m; i++) cnt[i] = 0;
		for (int i = 0; i < n; i++) cnt[r[i]]++;
		for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--cnt[r[idx[i]]]] = idx[i];
		nr[sa[0]] = 1;
		for (int i = 1; i < n; i++) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		for (int i = 0; i < n; i++) r[i] = nr[i];
		if (r[sa[n - 1]] == n) break;
	}
	return sa;
};

auto get_lcp = [](string s, auto sa) {
	int n = s.size();
	vector lcp(n - 1, 0), isa(n, 0);
	for (int i = 0; i < n; i++) isa[sa[i]] = i;
	for (int i = 0, k = 0; i < n; i++) if (isa[i]) {
		for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
		lcp[isa[i] - 1] = k ? k-- : 0;
	}
	return lcp;
};

auto sol = [](int n, auto v) {
	vector buc(0, vector(0, pair(0, 0)));
	vector c(0, pair(0, 0));
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		int val = j - i - v[i] + 1;
		if (val <= 0 && c.size()) {
			buc.push_back(c);
			c.clear();
		}
		if (val > 0) {
			c.push_back(pair(val == 1 ? 1 : 2, v[i]));
		}
	}
	if (c.size()) buc.push_back(c);
	string s;
	for (auto c : buc) {
		for (int i = 0; i < c.size(); i++) {
			s.push_back(c[i].second + 48);
			if (c[i].first == 2) {
				s.push_back('#');
				s.push_back(c[i].second + 48);
			}
		}
		s.push_back('#');
	}
	if (s.empty()) return i64(0);
	vector p(s.size(), 0);
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == '#') continue;
		if (i + 1 < s.size()) p[i] = p[i + 1] + 1;
		else p[i] = 1;
	}
	auto sa = get_sa(s);
	auto lcp = get_lcp(s, sa);
	i64 ret = 0;
	for (int i = 1; i < sa.size(); i++) {
		int v1 = lcp[i - 1];
		int v2 = p[sa[i]];
		ret += p[sa[i]] - min(v1, v2);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}