#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (b[a[i]] == i) continue;
		flag = false;
		break;
	}
	cout << (flag ? "Yes" : "No") << '\n';
}