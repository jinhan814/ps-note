#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	vector v(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) {
		if (s[i] != '?') continue;
		cin >> v[i][0] >> v[i][1];
	}
	auto cmp = [&](int i, int j) {
		return v[i][0] - v[i][1] > v[j][0] - v[j][1];
	};
	priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
	i64 ret = 0;
	for (int i = 0, x = 0; i < n; i++) {
		if (s[i] == '?') {
			s[i] = ')';
			ret += v[i][1];
			pq.push(i);
		}
		x += s[i] == '(' ? 1 : -1;
		if (x >= 0) continue;
		int p = pq.top(); pq.pop();
		s[p] = '(';
		ret += v[p][0] - v[p][1];
		x += 2;
	}
	cout << ret << '\n' << s << '\n';
}