#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, vector(n, 0));
	int x = 0, y = n / 2;
	v[x][y] = 1;
	for (int i = 2; i <= n * n; i++) {
		int nx = x - 1, ny = y + 1;
		if (nx < 0) nx += n;
		if (ny >= n) ny -= n;
		if (v[nx][ny]) {
			nx = x + 1;
			ny = y;
			if (nx >= n) nx -= n;
		}
		x = nx;
		y = ny;
		v[x][y] = i;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << v[i][j] << ' ';
		cout << '\n';
	}
}