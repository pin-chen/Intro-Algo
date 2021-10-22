#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
using namespace std;

int ans, n, m;
int R[20] = {};
int C[20] = {};

void solve(int x, bool *chessC, bool *chessD1, bool *chessD2){
	if(x == n - m){
		ans++;
	    return;
	}
	for(int y = 0; y < n - m; y++){
		bool temp =  chessC[C[y]] || chessD1[R[x] + C[y]] || chessD2[n - C[y] + R[x] - 1];
	    if(!temp){
	        chessD1[R[x]+C[y]] = true;
	        chessD2[n-C[y]+R[x]-1] = true;
	        chessC[C[y]] = true;
	        solve(x + 1, chessC, chessD1, chessD2);
			chessD1[R[x]+C[y]] = false;
	        chessD2[n-C[y]+R[x]-1] = false;
	        chessC[C[y]] = false;
	    }
	}
}

int main(){
	int t, k, i, x ,y;
	bool chessR[50] = {};
	bool chessC[50] = {};
	bool chessD1[2 * 50 - 1] = {};
	bool chessD2[2 * 50 - 1] = {};
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	in >> t;
	for(k = 0; k < t; k++){
		in >> n >> m;
		for(i = 0; i < n; i++){
			chessR[i] = false;
			chessC[i] = false;
		}
		for(i = 0; i < 2 * n - 1; i++){
			chessD1[i] = false;
			chessD2[i] = false;
		}
		for(i = 0; i < m; i++){
			in >> x >> y;
			chessR[x] = true;
			chessC[y] = true;
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
		}
		for(i = 0, x = 0; i < n; i++){
			if(!chessR[i]) R[x++] = i;
		}
		for(i = 0, x = 0; i < n; i++){
			if(!chessC[i]) C[x++] = i;
		}
		ans = 0;
		solve(0, chessC, chessD1, chessD2);
		out << ans << '\n';
	}
	return 0;
}
