#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
#include "data.hpp"
using namespace std;

int ans, n, m;
int R[20] = {};
int C[20] = {};

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
	int i, k, x, y;
	bool chessR[50] = {};
	bool chessC[50] = {};
	bool chessD1[2 * 50 - 1] = {};
	bool chessD2[2 * 50 - 1] = {};
	for(k = 0; k < test_data->t; k++){
		n = test_data->testcase[k].n;
		m = test_data->testcase[k].m;
		for(i = 0; i < n; i++){
			chessR[i] = false;
			chessC[i] = false;
		}
		for(i = 0; i < 2 * n - 1; i++){
			chessD1[i] = false;
			chessD2[i] = false;
		}
		for(i = 0; i < m; i++){
			x = test_data->testcase[k].preplace[i][0];
			y = test_data->testcase[k].preplace[i][1];
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
		X(0, chessC, chessD1, chessD2);
		out << ans << '\n';
	}
}
