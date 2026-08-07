#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, string s) {
	vector d(n, n);
	deque q(0, 0);
	for (int i = 0; i < n; i++) {
		if (s[i] == '.') continue;
		d[i] = 0;
		q.push_back(i);
	}
	while (q.size()) {
		int cur = q.front(); q.pop_front();
		for (int nxt : { cur - 1, cur + 1 }) {
			if (nxt < 0 || nxt >= n) continue;
			if (d[nxt] != n) continue;
			d[nxt] = d[cur] + 1;
			q.push_back(nxt);
		}
	}
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] <= m) continue;
		ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;
	cout << sol(n, m, s) << '\n';
}