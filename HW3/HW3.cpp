#include <iostream>
#include <fstream>
using namespace std;

unsigned long long ans = 0;
int Min, Max;

void solve(int x, int n, bool *chessC, bool *chessR, bool *chessD1, bool *chessD2){
	if(x == n){
		ans++;
	    return;
	}
	if(chessR[x]){
		solve(x + 1, n, chessC, chessR, chessD1, chessD2);
		return;
	}
	for(int y = Min; y < Max; y++){
		bool temp =  chessC[y] || chessD1[x + y] || chessD2[n - y + x - 1];
	    if(!temp){
	        chessD1[x+y] = true;
	        chessD2[n-y+x-1] = true;
	        chessR[x] = true;
	        chessC[y] = true;
	        solve(x + 1, n, chessC, chessR, chessD1, chessD2);
			chessD1[x+y] = false;
	        chessD2[n-y+x-1] = false;
	        chessR[x] = false;
	        chessC[y] = false;
	    }
	}
}

int main(){
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	int t, n, m, MIN = 0, MAX;
	in >> t;
	for(int k = 0; k < t; k++){
		in >> n >> m;
		Min = 0;
		Max = n;MAX = n;
		bool chessC[n] = {};
		bool chessR[n] = {};
		bool chessD1[2 * n - 1] = {};
		bool chessD2[2 * n - 1] = {};
		for(int i = 0; i < m; i++){
			int x, y;
			in >> x >> y;
			chessR[x] = true;
			chessC[y] = true;
			chessD1[x + y] = true;
			chessD2[n - y + x - 1] = true;
			Min = min(Min, y);
			Max = max(Max, y);
			MIN = min(MIN, x);
			MAX = max(MAX, x);
		}
		ans = 0;
		//if(n - m > 15) {
		//	out << ans << '\n';
		//	continue;
		//}
		solve(MIN, MAX, chessC, chessR, chessD1, chessD2);
		out << ans << '\n';
	}	
	return 0;
} 
