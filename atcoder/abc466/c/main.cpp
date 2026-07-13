#include <bits/stdc++.h>
using namespace std;

auto ask = [](int i, int j) {
	cout << "? " << i << ' ' << j << endl;
	string s; cin >> s;
	return s == "Yes";
};

int main() {
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		v[i] = i;
		if (i > 1) v[i] = max(v[i], v[i - 1]);
		while (v[i] + 1 <= n && ask(i, v[i] + 1)) v[i]++;
	}
	int res = 0;
	for (int i = 1; i <= n; i++) res += v[i] - i;
	cout << "! " << res << endl;
}