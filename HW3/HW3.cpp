#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

int ans = 0;
int R[24] = {};
//int C[24] = {};

void solve(int x, int s, int n, bool *chessD1, bool *chessD2, unordered_set<int> C, int e){
	if(x == s){
		ans++;
	    return;
	}
	if(e != -1)C.erase(e); 
	//if(chessR[R[x]]){
	//	solve(x + 1, s, n, chessC, chessR, chessD1, chessD2);
	//	return;
	//}
	for(auto y: C){
		bool temp = chessD1[R[x] + y] || chessD2[n - y + R[x] - 1];
	    if(!temp){
	        chessD1[R[x]+y] = true;
	        chessD2[n-y+R[x]-1] = true;
	        //chessR[R[x]] = true;
	        //chessC[y] = true;
	        solve(x + 1, s, n, chessD1, chessD2, C, y);
			chessD1[R[x]+y] = false;
	        chessD2[n-y+R[x]-1] = false;
	        //chessR[R[x]] = false;
	        //chessC[y] = false;
	    }
	}
}

int main(){
	ifstream in("input.txt", ios::in);
	ofstream out("output.txt", ios::out);
	int t, n, m;
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
		unordered_set<int> C;
		for(int i = 0, x = 0; i < n; i++){
			if(!chessC[i]) C.insert(i);
		}
		ans = 0;
		if(n - m > 20) {
			out << ans << '\n';
			continue;
		}
		
		solve(0, n - m, n, chessD1, chessD2, C, -1);
		out << ans << '\n';
	}	
	return 0;
}
