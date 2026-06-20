#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector buc(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			buc[x].push_back(i);
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << buc[i].size();
		for (int x : buc[i]) cout << ' ' << x;
		cout << '\n';
	}
}