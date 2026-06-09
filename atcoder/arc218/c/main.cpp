#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	vector ret(0, 0);
	deque dq(0, 0);
	for (int i = 2; i <= n; i++) dq.push_back(i);
	int x = 1;
	if (x == v[2]) {
		ret.push_back(1);
		swap(x, dq.front());
	}
	for (int i = 3; i <= n; i++) {
		if (x != v[i]) {
			while (dq.front() != v[i]) {
				ret.push_back(2);
				dq.push_back(dq.front());
				dq.pop_front();
			}
			ret.push_back(1);
			swap(x, dq.front());
		}
		while (dq.back() != v[i - 1]) {
			ret.push_back(2);
			dq.push_back(dq.front());
			dq.pop_front();
		}
		ret.push_back(1);
		swap(x, dq.front());
	}
	while (dq.front() != v[2]) {
		ret.push_back(2);
		dq.push_back(dq.front());
		dq.pop_front();
	}
	return ret;
};

int main() {
	int n; cin >> n;
	cout << 2 << endl;
	cout << "2 1";
	for (int i = 3; i <= n; i++) cout << ' ' << i;
	cout << endl;
	cout << "1";
	for (int i = 3; i <= n; i++) cout << ' ' << i;
	cout << " 2";
	cout << endl;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	auto res = sol(n, v);
	cout << res.size();
	for (int x : res) cout << ' ' << x;
	cout << endl;
}