#include <iostream>
#include <fstream>
using namespace std;

int ans = 0, n, m;
int R[24] = {};
int C[24] = {};

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
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	int t;
	in >> t;
	for(int k = 0; k < t; k++){
		in >> n >> m;
		bool chessR[n] = {};
		bool chessC[n] = {};
		bool chessD1[2 * n - 1] = {};
		bool chessD2[2 * n - 1] = {};
		for(int i = 0; i < m; i++){
			int x, y;
			in >> x >> y;
			chessR[x] = true;
			chessC[y] = true;
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
		}
		for(int i = 0, x = 0; i < n; i++){
			if(!chessR[i]) R[x++] = i;
		}
		for(int i = 0, x = 0; i < n; i++){
			if(!chessC[i]) C[x++] = i;
		}
		ans = 0;
		//if(n - m > 20) {
		//	out << ans << '\n';
		//	continue;
		//}
		solve(0, chessC, chessD1, chessD2);
		out << ans << '\n';
	}	
	return 0;
} 

//n=20 m=11
