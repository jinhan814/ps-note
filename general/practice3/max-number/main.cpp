#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end(), [](int a, int b) {
		string v1 = to_string(a) + to_string(b);
		string v2 = to_string(b) + to_string(a);
		return v1 > v2;
	});
	for (int i = 0; i < n; i++) cout << v[i] << ' ';
	cout << '\n';
}