#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
#include "data.hpp"
using namespace std;

int ans = 0, n, m;
int R[24] = {};
int C[24] = {};

void X(int x, bool *chessC, bool *chessD1, bool *chessD2){
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
	        X(x + 1, chessC, chessD1, chessD2);
			chessD1[R[x]+C[y]] = false;
	        chessD2[n-C[y]+R[x]-1] = false;
	        chessC[C[y]] = false;
	    }
	}
}

void solve(tTestData* test_data){
	ofstream out("output.txt", ios::out);
	for(int k = 0; k < test_data->t; k++){
		n = test_data->testcase[k].n;
		m = test_data->testcase[k].m;
		bool chessR[n] = {};
		bool chessC[n] = {};
		bool chessD1[2 * n - 1] = {};
		bool chessD2[2 * n - 1] = {};
		for(int i = 0; i < m; i++){
			int x = test_data->testcase[k].preplace[i][0];
			int y = test_data->testcase[k].preplace[i][1];
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
		if(n - m > 15) {
			out << ans << '\n';
			continue;
		}
		X(0, chessC, chessD1, chessD2);
		out << ans << '\n';
	}
}
