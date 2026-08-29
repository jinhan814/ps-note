#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	set s{ pair(0, 0) };
	s.clear();
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		bool flag = true;
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (!s.count(pair(a + dx, b + dy))) continue;
				flag = false;
				break;
			}
			if (!flag) break;
		}
		if (flag) s.insert(pair(a, b));
	}
	cout << s.size() << '\n';
}