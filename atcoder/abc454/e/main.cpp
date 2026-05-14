#include <bits/stdc++.h>
using namespace std;

string sol(int n, int a, int b) {
	if (n % 2 == 1) return "-1";
	if ((a + b) % 2 == 0) return "-1";
	if (n == 2) {
		if (a == 1 && b == 2) return "DR";
		if (a == 2 && b == 1) return "RD";
		assert(0);
		return "-1";
	}
	bool flag = a % 2 == 0;
	if (flag) {
		a = n + 1 - a;
		b = n + 1 - b;
	}
	string ret;
	if (a > 1) {
		for (int iter = 0; iter < (a - 1) / 2; iter++) {
			ret += string(n - 1, 'R');
			ret += "D";
			ret += string(n - 1, 'L');
			ret += "D";
		}
	}
	if (n - a + 1 == 2) {
		for (int iter = 0; iter < b / 2 - 1; iter++) {
			ret += "DRUR";
		}
		ret += "DR";
	}
	else if (b == 2) {
		for (int iter = 0; iter < (n - a + 1) / 2 - 1; iter++) {
			ret += "DRDL";
		}
		ret += "DR";
	}
	else {
		ret += string(b - 2, 'R');
		ret += "DRDL";
		for (int iter = 0; iter < b / 2 - 1; iter++) {
			ret += "LULD";
		}
		ret += "D";
		ret += string(b - 1, 'R');
		for (int iter = 0; iter < ((n - a + 1) - 4) / 2; iter++) {
			ret += "D";
			ret += string(b - 1, 'L');
			ret += "D";
			ret += string(b - 1, 'R');
		}
	}
	if (b < n) {
		for (int iter = 0; iter < (n - b) / 2; iter++) {
			ret += "R";
			ret += string(n - a, 'U');
			ret += "R";
			ret += string(n - a, 'D');
		}
	}
	if (flag) {
		reverse(ret.begin(), ret.end());
	}
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, a, b; cin >> n >> a >> b;
		string res = sol(n, a, b);
		if (res != "-1") {
			cout << "Yes" << '\n';
			cout << res << '\n';
		}
		else {
			cout << "No" << '\n';
		}
	}
}