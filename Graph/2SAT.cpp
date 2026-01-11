//G[i] := x_i is true; G[i+n] := x_i is false
//key : ( a or b ) is equal to ( !a => b and !b => a)
for (int i = 0; i < n; i++) {
	for (int j = i + 1; j < n; j++) {
		if (!(x_i && x_j)) {
			// ! (x_i && x_j) => !x_i or !x_j
			addedge(i, j + n);
			addedge(j, i + n);
		}
		if (! (x_i && !x_j)) {
			// ! (x_i && !x_j) => !x_i or x_j
			addedge(i, j);
			addedge(j + n, i + n);
		}
		if (! (!x_i && x_j)) {
			// ! (!x_i && x_j) -> x_i or !x_j
			addedge(i + n, j + n);
			addedge(j, i);
		}
		if (!(!x_i && !x_j)) {
			// !(!x_i && !x_j) => x_i or x_j
			addedge(i + n, j);
			addedge(j + n, i);
		}
	}
}
int num = scc(v);
for (int i = 0; i < n; i++) {
	if (id[i] == id[i + n]) cout << "NO\n",return;
}
cout << "YES\n";
for (int i = 0; i < n; i++) x[i] = (id[i + n] < id[i]);
//toposort !x before x <=> x is true. If tarjan, then (id[i + n] > id[i])
