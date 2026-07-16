#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string a, b; cin >> a >> b;
	int res = 1 << 30;
	for (int i = 0; i + b.size() - 1 < a.size(); i++) {
		int cnt = 0;
		for (int j = 0; j < b.size(); j++) {
			if (a[i + j] >= b[j]) cnt += a[i + j] - b[j];
			else cnt += a[i + j] - b[j] + 10;
		}
		res = min(res, cnt);
	}
	cout << res << '\n';
}