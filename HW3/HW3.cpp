#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
using namespace std;
int n, m, i, t, x, y;
int R[20];
int C[20];
bool chessR[50];
bool chessC[50];
bool chessD1[99];
bool chessD2[99];
void solve(int x){
	if(x == i){
		m++;
	    return;
	}
	int now_x = R[x];
	for(int y = 0; y < i; y++){
	    if(!(chessC[C[y]] || chessD1[now_x + C[y]]|| chessD2[n - C[y] + now_x - 1])){
	        chessD1[now_x + C[y]] = true;
	        chessD2[n - C[y] + now_x - 1] = true;
	        chessC[C[y]] = true;
	        solve(x + 1);
			chessD1[now_x + C[y]] = false;
	        chessD2[n - C[y]+ now_x - 1] = false;
	        chessC[C[y]]= false;
	    }
	}
}
int main(){
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	in >> t;
	while(t--){
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
		for(i = 0, x = 0, y = 0; i < n; i++){
			if(!chessR[i]) R[x++] = i;
			if(!chessC[i]) C[y++] = i;
		}
		i = n - m;
		m = 0;
		solve(0);
		out << m << '\n';
	}
	return 0;
}
