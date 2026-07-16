#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b; cin >> a >> b;
	int res = b % 7 - a % 7;
	if (res <= 0) res += 7;
	cout << res << '\n';
}