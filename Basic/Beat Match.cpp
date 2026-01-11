#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
using namespace std;

int main(){
	int t = 0;
	while(true){
		cout << "Test Case: " << ++t << '\n';
		system("gen.exe>data.in");
		system("Sol.exe<data.in>Sol.out");
		system("Bf.exe<data.in>Bf.out");
		if (system("fc Sol.out Bf.out")){
			break;
		}
	}
	return 0;
}
