#include "network.h"
#include <bits/stdc++.h>
using namespace std;

void findRoute(int n, int a, int b) {
	vector cache(n + 1, vector(n + 1, -1));
	auto f = [&](int i, int j) {
		if (i == j) return 0;
		if (cache[i][j] != -1) return cache[i][j];
		return cache[i][j] = ping(i, j) + 1;
	};
	while (a != b) {
		for (int i = 1; i <= n; i++) {
			if (f(i, b) != f(a, b) - 1) continue;
			if (f(a, i) != 1) continue;
			travelTo(i);
			a = i;
			break;
		}
	}
}