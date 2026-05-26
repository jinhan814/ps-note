#include <bits/stdc++.h>
using namespace std;

using f64 = double;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	cout << fixed << setprecision(20);
	cout << n * n * acos(-1) / 4 << '\n';
}