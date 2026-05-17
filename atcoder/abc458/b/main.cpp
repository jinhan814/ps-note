#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = i + "1012"[d] - '1';
				int ny = j + "2101"[d] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				cnt++;
			}
			cout << cnt << ' ';
		}
		cout << '\n';
	}
}