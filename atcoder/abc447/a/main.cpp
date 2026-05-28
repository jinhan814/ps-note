#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	cout << (m <= (n + 1) / 2 ? "Yes" : "No") << '\n';
}