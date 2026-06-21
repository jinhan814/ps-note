#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c, d; cin >> a >> b >> c >> d;
	bool flag = true;
	if (c < a || a + 100 <= c) flag = false;
	if (d < b || b + 100 <= d) flag = false;
	cout << (flag ? "Yes" : "No") << '\n';
}