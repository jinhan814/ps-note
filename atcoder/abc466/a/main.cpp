#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) { 
	for (int i = 0; i < n; i++) {
		if (v[i] < 0) continue;
		return false;
	}
	return true;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << (sol(n, v) ? "Yes" : "No") << '\n';
}