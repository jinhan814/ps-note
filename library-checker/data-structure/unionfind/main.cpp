#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) p[b] = a;
	}
private:
	vector<int> p;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	union_find uf(n);
	for (int i = 0; i < q; i++) {
		int op, a, b; cin >> op >> a >> b;
		if (op == 0) uf.merge(a, b);
		else cout << (uf.find(a) == uf.find(b)) << '\n';
	}
}